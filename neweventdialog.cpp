#include "neweventdialog.h"
#include "ui_neweventdialog.h"
#include "mongodbconnection.h"
#include "credential.h"
#include "aboutevent.h"
#include "newemaildialog.h"
#include <QMessageBox>

NewEventDialog::NewEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEventDialog)
{
    ui->setupUi(this);
}

NewEventDialog::~NewEventDialog()
{
    delete ui;
}

void NewEventDialog::on_exit_button_clicked()
{
    AboutEvent::initialize();
    this->close();
}

void NewEventDialog::on_sendmessage_checkbox_stateChanged(int clicked)
{
    if (clicked) {
        NewEmailDialog email;

        email.setModal(true);
        email.exec();
    } else {
        AboutEvent::set_to("");
        AboutEvent::set_subject("");
        AboutEvent::set_message("");
    }
}

void NewEventDialog::on_done_button_clicked()
{
    if (ui->eventname_input->text() == "" || ui->about_input->text() == "") {
        QMessageBox::critical(this, "Empty Fields", "Event Name and About Event fields cannot be empty");
        return;
    } else if (ui->sendmessage_checkbox->isChecked() &&
               (AboutEvent::get_to().empty() || AboutEvent::get_subject().empty() || AboutEvent::get_message().empty())) {
        QMessageBox::critical(this, "Confliction Detected", "Checkbox is checked but fields related to email are empty");
        return;
    } else {
        AboutEvent::set_event_name(ui->eventname_input->text().toStdString());
        AboutEvent::set_event_info(ui->about_input->text().toStdString());
        AboutEvent::set_is_send_message(ui->sendmessage_checkbox->isChecked());

        this->close();
    }
}
