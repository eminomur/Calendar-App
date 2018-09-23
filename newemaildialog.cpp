#include "newemaildialog.h"
#include "ui_newemaildialog.h"
#include "aboutevent.h"
#include <QMessageBox>

NewEmailDialog::NewEmailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEmailDialog)
{
    ui->setupUi(this);
}

NewEmailDialog::~NewEmailDialog()
{
    delete ui;
}

void NewEmailDialog::on_exit_button_clicked()
{
    AboutEvent::set_to("");
    AboutEvent::set_subject("");
    AboutEvent::set_message("");

    this->close();
}

void NewEmailDialog::on_done_button_clicked()
{
    if (ui->to_input->text() == "" || ui->subject_input->text() == "" || ui->message_input->toPlainText() == "") {
        QMessageBox::critical(this, "Empty Fields", "Empty fields are not allowed");
        return;
    }
    AboutEvent::set_to(ui->to_input->text().toStdString());
    AboutEvent::set_subject(ui->subject_input->text().toStdString());
    AboutEvent::set_message(ui->message_input->toPlainText().toStdString());

    this->close();
}
