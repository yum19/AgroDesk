#include "menu.h"
#include "ui_menu.h"
#include "login.h"
#include"GA_mainwindow.h"
#include"GM_mainwindow.h"
#include"mainwindow_gs.h"


menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_gestion_animaux_clicked() {
    mainwindow = new MainWindow();
    mainwindow->show();
    close();

}



/*void menu::on_gestion_section_clicked() {
    MainWindow_gs = new mainwindow_gs();
    MainWindow_gs->show();
    close();

}*/
/*
void menu::on_gestion_grains_clicked() {
    mainwindow = new MainWindow();
    mainwindow->show();
    close();

}

void menu::on_gestion_produit_clicked() {
    mainwindow = new MainWindow();
    mainwindow->show();
    close();

}*/



void menu::on_gestion_materiels_clicked()
{
    GM_Mainwindow = new GM_mainwindow();
    GM_Mainwindow->show();
     close();
}

void menu::on_gestion_produit_clicked()
{
    mainwindow_p = new MainWindow_gp();
    mainwindow_p->show();
    close();
}

void menu::on_gestion_sections_clicked()
{
    MainWindow_gs = new mainwindow_gs();
    MainWindow_gs->show();
    close();
}
