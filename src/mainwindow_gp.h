#ifndef MAINWINDOW_gp_H
#define MAINWINDOW_gp_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include<QMessageBox>
#include <QMainWindow>
#include"produit.h"
#include"ui_mainwindow_gp.h"
#include"arduino.h"
#include<QString>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow_gp; }
QT_END_NAMESPACE

class MainWindow_gp : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow_gp(QWidget *parent = nullptr);
    ~MainWindow_gp();

private slots:

    void on_ajouter_gp_clicked();

    void on_quitter_gp_clicked();

    //void on_radioButton_2_clicked();

    void on_modifier_gp_clicked();

    void on_pushButton_gp_clicked();

    void on_pb_recherche_gp_clicked();

    void on_supprimer_gp_clicked();

   // void on_refresh_clicked();

    void on_pb_statistique_gp_clicked();

   // void on_sellButton_clicked();

    void on_TRI_gp_clicked();

    void on_sellproduct_clicked();

    void on_refreshhgp_clicked();
    void displayLogHistory();

private:
    Ui::MainWindow_gp *ui;
    Produit Etmp;
    Produit E;
    Arduino A;
    QByteArray data;
    void updateProductInfo();

};
#endif
