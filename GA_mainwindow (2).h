#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include<QMessageBox>
#include <QMainWindow>
#include"animaux.h"
#include "QDateTime"
#include<QSystemTrayIcon>
#include "reminder.h"
#include <QtCharts>
#include <QChart>
#include <QChartView>
#include <QSerialPort>
#include "arduino.h"
QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void GA_showStatistics(QWidget *parent, QChartView *GA_chartView);

private slots:

    void on_GA_ajouter_clicked();

    void on_GA_modifier_clicked();

    void on_GA_supprimer_clicked();

    void GA_updateTableView1();

    void GA_updateTableView2();

    void on_GA_analyzeButton_clicked();

    void on_GA_showRemindersButton_clicked();

    void on_GA_addReminderButton_clicked();

    void on_GA_calculateProbabilityButton_clicked();

    void GA_checkReminders();

    void on_GA_rechercherButton_clicked();

    void on_GA_trierButton_clicked();

    void on_GA_resetButton_clicked();

    void on_GA_exportToPDF_clicked();

    void on_GA_stat_clicked();

    void on_GA_quitter_clicked();

    void on_GA_manualButton_clicked();

   //void on_login_2_clicked();


private:
    Ui::MainWindow *ui;
    Animaux GA_Etmp,GA_p,GA_p1;
    Animaux Animal;
    Animaux animaux;
    QSystemTrayIcon *GA_trayIcon;
    Reminder reminder;
    QComboBox* GA_symptomComboBox1;
    QComboBox* GA_symptomComboBox2;
    QComboBox* GA_symptomComboBox3;
    QPushButton* GA_calculateProbabilityButton;
    QLineEdit* GA_resultLineEdit;
   Arduino GA_A;
   QByteArray GA_data;
   QByteArray data;
   int inc = 0;
   QSerialPort *GA_serialPort;


/*public:
    // Other member functions...

    void showStatistics(QWidget *parent, QChartView *chartView);*/



    //QSqlDatabase animalDb;

    //QDateTime dt;
};
#endif // MAINWINDOW_H
