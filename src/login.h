#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include"menu.h"
#include <QSqlError>
#include <QSqlQuery>
#include "GA_mainwindow.h"
#include"GM_mainwindow.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
signals:
    void dataAvailabe(const QString &data);

private slots:
    void on_login_2_clicked();

private:
    Ui::login *ui;
    QSqlDatabase db;
    menu *menu1;
};

#endif // LOGIN_H
