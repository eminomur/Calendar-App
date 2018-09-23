#include "mainwindow.h"
#include <QApplication>
#include <mongocxx/instance.hpp>

int main(int argc, char *argv[])
{
    // This should be done only once
    mongocxx::instance instance{};

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
