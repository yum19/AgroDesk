#ifndef MAINWINDOW_gs_H
#define MAINWINDOW_gs_H
#include"arduino.h"
#include"section.h"
#include"connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include<QMessageBox>

#include<QApplication>
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow_gs; }
QT_END_NAMESPACE

class mainwindow_gs : public QDialog
{
    Q_OBJECT

public:
    mainwindow_gs(QWidget *parent = nullptr);
    ~mainwindow_gs();

private slots:




    void on_ajouter_GS_clicked();

    void on_pushButton_3_GS_clicked();

    void on_modifier_2_GS_clicked();

    void on_chercher_2_GS_clicked();

    void on_pdf_2_GS_clicked();

    void on_trier_GS_clicked();

    void on_displayTypeStatistics_2_GS_clicked();

    void on_displayTypeStatistics_4_GS_clicked();

    void on_displayTypeStatistics_GS_clicked();

    void on_tableView_GS_activated(const QModelIndex &index);

    void on_pushButton_GS_clicked();

private:
    Ui::mainwindow_gs *ui;
        QByteArray data;
        Arduino a;
        client c;

};
#endif // MAINWINDOW_gs_H
