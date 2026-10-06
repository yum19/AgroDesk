#include "GA_mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include<QDebug>
#include "login.h"
#include "menu.h"
#include"GM_mainwindow.h"
#include"mainwindow_gp.h"
#include"mainwindow_gs.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnect();
    //MainWindow w;
   //GM_mainwindow gm;
    login l;
   // menu m;
    if(test)
    {
        //w.show();
        l.show();
       // m.show();
        //gm.show();
        QMessageBox::information(nullptr, QObject::tr("la base de données est ouverte"),
                    QObject::tr("connexion réussie.\n"
                                "Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("la base de données n'est pas ouverte"),
                    QObject::tr("la connexion a échoué.\n"
                                "Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);



    return a.exec();
}
