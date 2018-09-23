#include "selectedeventdialog.h"
#include "ui_selectedeventdialog.h"
#include "mongodbconnection.h"
#include "credential.h"
#include <string>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include "aboutevent.h"
#include <QMessageBox>

SelectedEventDialog::SelectedEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectedEventDialog)
{
    ui->setupUi(this);
    // To connect database
    connection = new MongoDBConnection("mongodb://xyz:1@cluster0-shard-00-00-ohmfr.gcp.mongodb.net:27017,cluster0-shard-00-01-ohmfr.gcp.mongodb.net:27017,"
                                       "cluster0-shard-00-02-ohmfr.gcp.mongodb.net:27017/test?ssl=true&replicaSet=Cluster0-shard-0&authSource=admin&"
                                       "retryWrites=true", "calendar", Credential::get_id());

    ui->eventname_input->setText(AboutEvent::get_event_name().c_str());
    ui->about_input->setText(AboutEvent::get_event_info().c_str());
    if (AboutEvent::get_is_send_message()) {
        ui->sendmessage_checkbox->setChecked(true);
    }
    ui->to_input->setText(AboutEvent::get_to().c_str());
    ui->subject_input->setText(AboutEvent::get_subject().c_str());
    ui->message_input->setPlainText(AboutEvent::get_message().c_str());
}

SelectedEventDialog::~SelectedEventDialog()
{
    // To return allocated memory to freestore
    delete connection;
    delete ui;
}

void SelectedEventDialog::on_close_button_clicked()
{
    this->close();
}

void SelectedEventDialog::on_delete_button_clicked()
{
    bsoncxx::builder::stream::document document{};

    document << "date" << AboutEvent::get_selected_date()
             << "eventname" << ui->eventname_input->text().toStdString()
             << "aboutevent" << ui->about_input->text().toStdString()
             << "sendmessage" << ui->sendmessage_checkbox->isChecked()
             << "to" << ui->to_input->text().toStdString()
             << "subject" << ui->subject_input->text().toStdString()
             << "message" << ui->message_input->toPlainText().toStdString();

    connection->get_collection().find_one_and_delete(document.view());
    this->close();
}

void SelectedEventDialog::on_modify_button_clicked()
{
    if (ui->eventname_input->text() == "" || ui->about_input->text() == "") {
        QMessageBox::critical(this, "Error", "Fill required fields properly");
        return;
    }

    if (ui->sendmessage_checkbox->isChecked() &&
            (ui->to_input->text() == "" || ui->subject_input->text() == "" || ui->message_input->toPlainText() == "")) {
        QMessageBox::critical(this, "Confliction detected", "Checkbox is checked but fields related to email are empty");
        return;
    }

    bsoncxx::builder::stream::document actual_document;

    actual_document << "date" << AboutEvent::get_selected_date()
                    << "eventname" << AboutEvent::get_event_name()
                    << "aboutevent" << AboutEvent::get_event_info()
                    << "sendmessage" << AboutEvent::get_is_send_message()
                    << "to" << AboutEvent::get_to()
                    << "subject" << AboutEvent::get_subject()
                    << "message" << AboutEvent::get_message();

    bsoncxx::builder::stream::document new_document{};

    new_document << "date" << AboutEvent::get_selected_date()
                 << "eventname" << ui->eventname_input->text().toStdString()
                 << "aboutevent" << ui->about_input->text().toStdString()
                 << "sendmessage" << ui->sendmessage_checkbox->isChecked()
                 << "to" << ui->to_input->text().toStdString()
                 << "subject" << ui->subject_input->text().toStdString()
                 << "message" << ui->subject_input->text().toStdString();

    connection->get_collection().find_one_and_update(actual_document.view(), new_document.view());
    this->close();
}
