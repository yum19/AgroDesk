#ifndef ANIMAUX_H
#define ANIMAUX_H
#include<QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QtSql>
#include<QString>
#include <QDateTime>
#include<reminder.h>
#include <QMap>


class Animaux
{
public:

    Animaux();
    Animaux(int,int,QString,QString,QString,QString,QString,QString,QString);
    Animaux(int,int);




    int getGA_id();
    int getGA_poids();
    QString getGA_type();
    QString getGA_sexe();
    QString getGA_date_enter();
    QString getGA_date_sortie();
    QString getGA_dernier_vaccination();
    QString getGA_prochaine_vaccination();
    QString getGA_malade();


     void setGA_id(int);
     void setGA_poids(int);
     void setGA_type(QString);
     void setGA_sexe(QString);
     void setGA_date_enter(QString);
     void setGA_date_sortie(QString);
     void setGA_dernier_vaccination(QString);
     void setGA_prochaine_vaccination(QString);
     void setGA_malade(QString);


     bool GA_ajouter();
     QSqlQueryModel *GA_afficher();
     bool GA_supprimer(int);
     bool GA_modifier(int);
     bool GA_afficherMaladeOui(QString);
     QString GA_getprochaine_vaccination() const;
     QString getGA_type() const;
     int getGA_id() const;
     QList<Animaux> GA_getAnimals();
     void GA_analyzeAndSetReminders();
     bool GA_isAnimalSick(int GA_id, QString &errorMessage);

     bool GA_checkIfAnimalExists(int GA_id);
     bool GA_isAnimalHealthy(int GA_id);
     QSqlQueryModel* GA_getAnimalTable();
     QString GA_calculateIllness(QComboBox* GA_comboBox1, QComboBox* GA_comboBox2, QComboBox* GA_comboBox3);
     bool GA_ajouter2();









 private:
    int GA_id;
    int GA_poids;
    QString GA_type,GA_sexe, GA_date_sortie, GA_dernier_vaccination, GA_prochaine_vaccination,GA_malade;
    QString GA_date_enter;
    QSqlDatabase db;


};


#endif // ANIMAUX_H
