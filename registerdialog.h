#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "mongodbconnection.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:

    void on_register_button_clicked();

private:
    Ui::RegisterDialog *ui;
    MongoDBConnection *connection;
};

#endif // REGISTERDIALOG_H
