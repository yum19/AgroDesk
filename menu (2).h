#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include"GA_mainwindow.h"
#include"GM_mainwindow.h"
#include"mainwindow_gp.h"
#include"mainwindow_gs.h"
namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_gestion_animaux_clicked();
    //void on_gestion_grains_clicked();

    //void on_gestion_produit_clicked();

    //void showMainWindow();
    void on_gestion_materiels_clicked();

    void on_gestion_produit_clicked();


    void on_gestion_sections_clicked();

private:
    Ui::menu *ui;
    MainWindow *mainwindow;
    GM_mainwindow *GM_Mainwindow;
    mainwindow_gs *MainWindow_gs;
    MainWindow_gp * mainwindow_p;
};

#endif // MENU_H
