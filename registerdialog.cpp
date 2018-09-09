#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_register_button_clicked()
{
    QString firstname = ui->firstname_input->text();
    QString lastname = ui->lastname_input->text();
    QString username = ui->username_input->text();
    QString password = ui->password_input->text();
}
