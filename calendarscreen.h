#ifndef CALENDARSCREEN_H
#define CALENDARSCREEN_H

#include <QDialog>
#include "mongodbconnection.h"
#include <string>

namespace Ui {
class CalendarScreen;
}

class CalendarScreen : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarScreen(QWidget *parent = nullptr);
    ~CalendarScreen();

private slots:
    void on_newevent_button_clicked();

    void on_today_button_clicked();

    void on_event_table_doubleClicked(const QModelIndex &index);

    void on_calendar_clicked(const QDate &date);

private:
    Ui::CalendarScreen *ui;
    MongoDBConnection *connection;

    void add_new_event();
    void list_events(const std::string& selected_date) const;
    void check_for_events_with_email(const std::string& current_date);
};

#endif // CALENDARSCREEN_H
