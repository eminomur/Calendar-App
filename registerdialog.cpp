#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <QMessageBox>
#include "mongodbconnection.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    // To connect database
    connection = new MongoDBConnection("mongodb://xyz:1@cluster0-shard-00-00-ohmfr.gcp.mongodb.net:27017,cluster0-shard-00-01-ohmfr.gcp.mongodb.net:27017,"
                                       "cluster0-shard-00-02-ohmfr.gcp.mongodb.net:27017/test?ssl=true&replicaSet=Cluster0-shard-0&authSource=admin&"
                                       "retryWrites=true", "calendar", "userlist");
}

RegisterDialog::~RegisterDialog()
{
    // To return allocated memory to freestore
    delete connection;
    delete ui;
}

void RegisterDialog::on_register_button_clicked()
{
    QString email = ui->emal_input->text();
    QString email_password = ui->emailpassword_input->text();
    QString firstname = ui->firstname_input->text();
    QString lastname = ui->lastname_input->text();
    QString username = ui->username_input->text();
    QString password = ui->password_input->text();

    // Boxes are checked whether they are empty or not
    // Empty boxes are forbidden
    if (email.isEmpty() ||
            email_password.isEmpty() ||
            firstname.isEmpty() ||
            lastname.isEmpty() ||
            username.isEmpty() ||
            password.isEmpty()) {
        QMessageBox::critical(this, "Empty Box", "Empty boxes are not allowed");
        return;
    }

    bsoncxx::builder::stream::document document{};

    // Checking for username is unique or not
    document << "username" << username.toStdString().c_str();
    std::int64_t username_length = connection->get_collection().count(document.view());

    // Since duplicate username is not allowed
    // It is checked if username is unique or not
    if (username_length != 0) {
        QMessageBox::critical(this, "Username Exists", "This username has been taken before");
        return;
    }
    document.clear();

    // Checking for email is unique or not
    document << "email" << email.toStdString().c_str();
    std::int64_t email_length = connection->get_collection().count(document.view());

    // Since duplicate email is not allowed
    // It is checked if email is unique or not
    if (email_length != 0) {
        QMessageBox::critical(this, "E-mail Exists", "User with this e-mail address already exists");
        return;
    }
    document.clear();

    // Inserts document into the collection
    document << "email" << email.toStdString()
             << "emailpassword" << email_password.toStdString()
             << "firstname" << firstname.toStdString()
             << "lastname" << lastname.toStdString()
             << "username" << username.toStdString()
             << "password" << password.toStdString();

    connection->get_collection().insert_one(document.view());

    // When registration is done, widget is closed
    this->close();
}
