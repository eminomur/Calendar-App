#ifndef NEWEMAILDIALOG_H
#define NEWEMAILDIALOG_H

#include <QDialog>

namespace Ui {
class NewEmailDialog;
}

class NewEmailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEmailDialog(QWidget *parent = nullptr);
    ~NewEmailDialog();

private slots:
    void on_exit_button_clicked();

    void on_done_button_clicked();

private:
    Ui::NewEmailDialog *ui;
};

#endif // NEWEMAILDIALOG_H
