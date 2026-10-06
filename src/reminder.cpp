#include "reminder.h"
#include <QDateTime>

void Reminder::addReminder(const QString &text, const QDateTime &dateTime) {
    ReminderInfo info;
    info.text = text;
    info.dateTime = dateTime;
    reminders.append(info);
}

QList<ReminderInfo> Reminder::getUpcomingReminders() {
    QList<ReminderInfo> upcomingReminders;
    QDateTime currentDateTime = QDateTime::currentDateTime();

    for (const ReminderInfo& info : reminders) {
        if (info.dateTime > currentDateTime) {
            upcomingReminders.append(info);
        }
    }

    return upcomingReminders;
}
