#ifndef SELECTEDEVENTDIALOG_H
#define SELECTEDEVENTDIALOG_H

#include <QDialog>
#include <mongodbconnection.h>

namespace Ui {
class SelectedEventDialog;
}

class SelectedEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectedEventDialog(QWidget *parent = nullptr);
    ~SelectedEventDialog();

private slots:
    void on_close_button_clicked();

    void on_delete_button_clicked();

    void on_modify_button_clicked();

private:
    Ui::SelectedEventDialog *ui;
    MongoDBConnection *connection;
};

#endif // SELECTEDEVENTDIALOG_H
