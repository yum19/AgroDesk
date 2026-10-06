#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "animaux.h"
#include"connection.h"
#include<QMessageBox>
#include<QApplication>
#include"GA_mainwindow.h"
#include <QComboBox>
#include <QIntValidator>
#include "ui_GA_mainwindow.h"
#include<QDateTime>
#include "reminder.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTextCursor>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include"GM_mainwindow.h"
#include"mainwindow_gs.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("ahmed03");//inserer nom de l'utilisateur
    db.setPassword("ahmed03");//inserer mot de passe de cet utilisateur



    if (!db.open())
        ui->label_7->setText ("failed to open the database");
    else
    ui->label_7->setText("connected....");
}




login::~login()
{
    delete ui;
}

void login::on_login_2_clicked()
{
        QString name = ui->nom->text();
        QString prenom = ui->prenom->text();
        QString password = ui->password->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM login WHERE name = :name AND prenom = :prenom AND password = :password");
        query.bindValue(":name", name);
        query.bindValue(":prenom", prenom);
        query.bindValue(":password", password);
        if (db.isOpen()){
            if (query.exec() && query.next()) {
                QMessageBox::information(this, "Login", "Username and password are correct");
                hide();
                menu1 = new menu(this);
                menu1->show();

            } else {
                QMessageBox::warning(this, "Login", "Username and password are incorrect");
            }
        }else {qDebug()<<"Filed to open the database";
            return;}

}
