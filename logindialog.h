#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mongodbconnection.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_login_button_clicked();

private:
    Ui::LoginDialog *ui;
    MongoDBConnection *connection;
};

#endif // LOGINDIALOG_H
