#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registerdialog.h"
#include "logindialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_button_clicked()
{
    LoginDialog dialog;

    dialog.setModal(true);
    this->close();
    dialog.exec();
    this->show();
}

void MainWindow::on_register_button_clicked()
{
    RegisterDialog dialog;

    dialog.setModal(true);
    this->close();
    dialog.exec();
    this->show();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "A simple calendar app.\nCreated by Muhammed Emin ÖMÜR. I am studying software engineering.");
}

void MainWindow::on_actionBefore_Starting_triggered()
{
    QMessageBox::about(this, "Before Start", "To use this program you need MongoDB (Cloud Database is Preferred).\n"
                       "To send email POCO (Portable Component) was used.\n"
                       "Program does not check validity of input you enter so you must provide this yourself.\n"
                       "Since this program does not support two steps validation and only works with Gmail\n"
                       "you have to generate an application specific password to by-pass two steps validation.\n"
                       "If you see something wrong with program please inform me.");
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
