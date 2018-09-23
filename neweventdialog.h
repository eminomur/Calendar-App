#ifndef NEWEVENTDIALOG_H
#define NEWEVENTDIALOG_H

#include <QDialog>
#include "mongodbconnection.h"

namespace Ui {
class NewEventDialog;
}

class NewEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEventDialog(QWidget *parent = nullptr);
    ~NewEventDialog();

private slots:
    void on_exit_button_clicked();

    void on_sendmessage_checkbox_stateChanged(int arg1);

    void on_done_button_clicked();

private:
    Ui::NewEventDialog *ui;
};

#endif // NEWEVENTDIALOG_H
