#include "calendarscreen.h"
#include "ui_calendarscreen.h"
#include "credential.h"
#include "neweventdialog.h"
#include "mongodbconnection.h"
#include "aboutevent.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <string>
#include <QTableWidgetItem>
#include "selectedeventdialog.h"
#include "sendemail.h"
#include <QMessageBox>

CalendarScreen::CalendarScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarScreen)
{
    ui->setupUi(this);

    // To connect database
    connection = new MongoDBConnection("mongodb://xyz:1@cluster0-shard-00-00-ohmfr.gcp.mongodb.net:27017,cluster0-shard-00-01-ohmfr.gcp.mongodb.net:27017,"
                                       "cluster0-shard-00-02-ohmfr.gcp.mongodb.net:27017/test?ssl=true&replicaSet=Cluster0-shard-0&authSource=admin&"
                                       "retryWrites=true", "calendar", Credential::get_id());

    // When screen is loaded initially to show current events in today
    // following code is executed
    list_events(QDate::currentDate().toString("dd/MM/yyyy").toStdString());

    // Following function will check if there is an event which email have to sent today
    check_for_events_with_email(QDate::currentDate().toString("dd/MM/yyyy").toStdString());
}

CalendarScreen::~CalendarScreen()
{
    // To return allocated memory to freestore
    delete connection;
    delete ui;
}

void CalendarScreen::on_newevent_button_clicked()
{
    NewEventDialog event;

    event.setModal(true);
    event.exec();

    if (!AboutEvent::is_initialized()) {
        add_new_event();
        AboutEvent::initialize();
    }
}

void CalendarScreen::add_new_event()
{
    bsoncxx::builder::stream::document document{};

    document << "date" << ui->calendar->selectedDate().toString("dd/MM/yyyy").toStdString()
             << "eventname" << AboutEvent::get_event_name()
             << "aboutevent" << AboutEvent::get_event_info()
             << "sendmessage" << AboutEvent::get_is_send_message()
             << "to" << AboutEvent::get_to()
             << "subject" << AboutEvent::get_subject()
             << "message" << AboutEvent::get_message();

    AboutEvent::initialize();
    connection->get_collection().insert_one(document.view());
    list_events(ui->calendar->selectedDate().toString("dd/MM/yyyy").toStdString());
}

void CalendarScreen::on_today_button_clicked()
{
    ui->calendar->setSelectedDate(QDate(QDate::currentDate()));
}

void CalendarScreen::on_event_table_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    AboutEvent::initialize();
    AboutEvent::set_selected_date(ui->calendar->selectedDate().toString("dd/MM/yyyy").toStdString());
    AboutEvent::set_event_name(ui->event_table->item(row, 0)->text().toStdString());
    AboutEvent::set_event_info(ui->event_table->item(row, 1)->text().toStdString());
    AboutEvent::set_is_send_message((ui->event_table->item(row, 2)->text() == "true") ? true : false);
    AboutEvent::set_to(ui->event_table->item(row, 3)->text().toStdString());
    AboutEvent::set_subject(ui->event_table->item(row, 4)->text().toStdString());
    AboutEvent::set_message(ui->event_table->item(row, 5)->text().toStdString());

    SelectedEventDialog dialog;

    dialog.setModal(true);
    dialog.exec();

    list_events(ui->calendar->selectedDate().toString("dd/MM/yyyy").toStdString());
}

// This is used to update event list for selected date
void CalendarScreen::on_calendar_clicked(const QDate &date)
{
    list_events(date.toString("dd/MM/yyyy").toStdString());
}

void CalendarScreen::list_events(const std::string& selected_date) const
{
    // Before loading event list, current list is removed by the following code
    ui->event_table->setRowCount(0);

    bsoncxx::builder::stream::document document{};

    document << "date" << selected_date;

    mongocxx::cursor event_list = connection->get_collection().find(document.view());

    int row_number = 0;
    for (auto& event : event_list) {
        AboutEvent::initialize(bsoncxx::to_json(event));

        ui->event_table->insertRow(row_number);

        ui->event_table->setItem(row_number, 0, new QTableWidgetItem(AboutEvent::get_event_name().c_str()));
        ui->event_table->setItem(row_number, 1, new QTableWidgetItem(AboutEvent::get_event_info().c_str()));
        ui->event_table->setItem(row_number, 2, new QTableWidgetItem((AboutEvent::get_is_send_message() == true) ? "true" : "false"));
        ui->event_table->setItem(row_number, 3, new QTableWidgetItem(AboutEvent::get_to().c_str()));
        ui->event_table->setItem(row_number, 4, new QTableWidgetItem(AboutEvent::get_subject().c_str()));
        ui->event_table->setItem(row_number, 5, new QTableWidgetItem(AboutEvent::get_message().c_str()));

        ++row_number;
    }
}

void CalendarScreen::check_for_events_with_email(const std::string& current_date)
{
    std::string result;
    bsoncxx::builder::stream::document document{};

    document << "date" << current_date
             << "sendmessage" << true;

    mongocxx::cursor event_list = connection->get_collection().find(document.view());

    for (auto& event : event_list) {
        AboutEvent::initialize(bsoncxx::to_json(event));
        result = SendEmail::send();

        if (result != "") {
            QMessageBox::critical(this, "Email Error", result.c_str());
        } else {
            connection->get_collection().find_one_and_update(
                        bsoncxx::builder::stream::document{} << "date" << current_date
                                                             << "eventname" << AboutEvent::get_event_name()
                                                             << "aboutevent" << AboutEvent::get_event_info()
                                                             << "sendmessage" << AboutEvent::get_is_send_message()
                                                             << "to" << AboutEvent::get_to()
                                                             << "subject" << AboutEvent::get_subject()
                                                             << "message" << AboutEvent::get_message()
                                                             << bsoncxx::builder::stream::finalize,
                        bsoncxx::builder::stream::document{} << "date" << current_date
                                                             << "eventname" << AboutEvent::get_event_name()
                                                             << "aboutevent" << AboutEvent::get_event_info()
                                                             << "sendmessage" << false
                                                             << "to" << AboutEvent::get_to()
                                                             << "subject" << AboutEvent::get_subject()
                                                             << "message" << AboutEvent::get_message()
                                                             << bsoncxx::builder::stream::finalize);
        }
    }
}
