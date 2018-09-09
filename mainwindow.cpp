#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mongocxx/instance.hpp>
#include <QMessageBox>
#include <registerdialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // This should be done only once
    mongocxx::instance instance{};
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 2 farklı ekran tasarla biri login için öteki register için
// Modal olsun, eğer giriş işi hallolursa ana ekran yok olsun yerine takvim ekranı gelir
// Diğerinde bu yok
void MainWindow::on_login_button_clicked()
{

}

void MainWindow::on_register_button_clicked()
{
    RegisterDialog dialog;

    dialog.setModal(true);
    dialog.exec();
}
