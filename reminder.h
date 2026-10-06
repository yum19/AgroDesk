#ifndef REMINDER_H
#define REMINDER_H

#include <QList>
#include <QString>
#include <QDateTime>



struct ReminderInfo {
    QString text;
    QDateTime dateTime;
};

class Reminder
{
public:
    void addReminder(const QString& text, const QDateTime& dateTime);
    QList<ReminderInfo> getUpcomingReminders();

private:
    QList<ReminderInfo> reminders;
};

#endif // REMINDER_H
