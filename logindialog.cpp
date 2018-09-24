#include "logindialog.h"
#include "ui_logindialog.h"
#include "mongodbconnection.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <QMessageBox>
#include "credential.h"
#include "calendarscreen.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    // To connect database
    connection = new MongoDBConnection(/* Enter your connection parameter here */);
}

LoginDialog::~LoginDialog()
{
    // To return allocated memory to freestore
    delete connection;
    delete ui;
}

void LoginDialog::on_login_button_clicked()
{
    QString username = ui->username_input->text();
    QString password = ui->password_input->text();

    bsoncxx::builder::stream::document document{};

    document << "username" << username.toStdString()
             << "password" << password.toStdString();

    bsoncxx::stdx::optional<bsoncxx::document::value> result = connection->get_collection().find_one(document.view());

    if (result) {
        // This code is essential because after log in
        // We need to know who is user to achive user specific actions
        Credential::initialize_credential(bsoncxx::to_json(result->view()));

        // This will be used to open calendar screen
        CalendarScreen screen;

        screen.setModal(true);
        this->close();
        screen.exec();
    } else {
        QMessageBox::warning(this, "Error", "There is no user with this username and password");
    }
}
