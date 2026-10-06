#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDialog>
#include <QString>
#include "matriel.h"
#include <QSqlQuery>
#include <QObject>
#include <QMessageBox>
#include "connection.h"

Matriel::Matriel()
{
    id_mat = 0;
    nom_mat = "";
    GM_etat = "";
    GM_prix = 0;
    GM_fonctionnalite = "";
    id_section = 0;
}
Matriel::Matriel(int id_mat,QString nom_mat,QString GM_etat,int GM_prix,QString GM_fonctionnalite ,int id_section )
{
    this->id_mat = id_mat;
    this->nom_mat = nom_mat;
    this->GM_etat = GM_etat;
    this->GM_prix =GM_prix;
    this->GM_fonctionnalite = GM_fonctionnalite;
    this->id_section = id_section ;
}

int Matriel::getid_mat() { return id_mat; }
QString Matriel::getnom_mat() { return nom_mat; }
QString Matriel::getetat() { return GM_etat; }
double Matriel::getprix() { return GM_prix; }
QString Matriel::getfonctionnalite() { return GM_fonctionnalite; }
int Matriel::getid_section() { return id_section; }


void Matriel::setid_mat(int id_mat) { this->id_mat = id_mat; }
void Matriel::setnom_mat(QString nom_mat) { this->nom_mat = nom_mat; }
void Matriel::setetat(QString GM_etat) { this->GM_etat = GM_etat; }
void Matriel::setprix(double GM_prix) {this-> GM_prix = GM_prix; }
void Matriel::setfonctionnalite(QString GM_fonctionnalite) { this ->GM_fonctionnalite = GM_fonctionnalite; }
void Matriel::setid_section(int id_section) { this ->id_section = id_section; }


bool Matriel::GM_ajouter()
{

QSqlQuery query;

query.prepare("INSERT INTO MATERIEL(id_mat,nom_mat,etat,prix,fonctionnalite,id_section)"
              "VALUES(:id_mat,:nom_mat,:etat,:prix,:fonctionnalite,:id_section)");

query.bindValue(":id_mat",id_mat);
query.bindValue(":nom_mat",nom_mat);
query.bindValue(":etat",GM_etat);
query.bindValue(":prix",GM_prix);
query.bindValue(":fonctionnalite",GM_fonctionnalite);
query.bindValue(":id_section",id_section);

return  query.exec();
}

QSqlQueryModel * Matriel::GM_afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM  MATERIEL ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_mat"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_mat"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonctionnalite"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_section"));
     return model;
}

bool Matriel::GM_supprimer(int id_mat)
{

        QSqlQuery query;
        QString res=QString ::number(id_mat);
        query.prepare("DELETE FROM MATERIEL WHERE id_mat = :id_mat");
        query.bindValue(":id_mat", id_mat);
        return query.exec();

 }

bool Matriel::GM_modifier(int id_mat)
{
        //  bool test=false;
    QString res = QString::number(id_mat);


        QSqlQuery query;

        query.prepare("UPDATE  MATERIEL SET id_mat=:id_mat, nom_mat=:nom_mat, etat=:etat, prix=:prix, fonctionnalite=:fonctionnalite, id_section=:id_section where id_mat=:id_mat");

        query.bindValue(":id_mat",id_mat);
        query.bindValue(":nom_mat",nom_mat);
        query.bindValue(":etat",GM_etat);
        query.bindValue(":prix",GM_prix);
        query.bindValue(":Fonctionnalite",GM_fonctionnalite);
        query.bindValue(":id_section",id_section);

        return query.exec();
     }


QSqlQueryModel * Matriel::GM_recherche(int id_mat)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM MATERIEL WHERE id_mat LIKE '" + QString::number(id_mat) + "'");

    return model;
}


QSqlQueryModel* Matriel::GM_sort_tri_UP()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM MATERIEL ORDER BY id_mat ASC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_mat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_mat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonctionnalite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_section"));

        return model;
}

QSqlQueryModel* Matriel::GM_sort_tri_DOWN()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM MATERIEL ORDER BY id_mat DESC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_mat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_mat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonctionnalite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_section"));
        return model;
}


QString MaintenanceReparation::getMaterielEnPanne(int id_mat) {
    QString materiel = "";

    Connection db;

    if (db.createconnect()) {
        QSqlQuery query;
        query.prepare("SELECT etat FROM MATERIEL WHERE id_mat = :id_mat");
        query.bindValue(":id_mat", id_mat);

        if (query.exec() && query.next()) {
            QString GM_etat = query.value(0).toString();

            if (GM_etat == "dispo") {
                materiel = "Le matériel est disponible.";
            } else if (GM_etat == "en panne") {
                materiel = "Matériel en panne.";
            } else {
                materiel = "État du matériel inconnu : " + GM_etat;
            }
        } else {
            qDebug() << "Erreur de requête : " << query.lastError().text();
        }
    } else {
        qDebug() << "Impossible d'ouvrir la base de données : " << QSqlDatabase::database().lastError().text();
    }

    return materiel;
}

void MaintenanceReparation::reparerMateriel(int id_mat) {
    qDebug() << "ID du matériel à réparer : " << id_mat;

    Connection db;

    if (db.createconnect()) {
        QSqlQuery query;
        query.prepare("UPDATE MATERIEL SET etat = 'dispo' WHERE id_mat = :id_mat");
        query.bindValue(":id_mat", id_mat);

        if (query.exec()) {
            qDebug() << "Réparation réussie.";
        } else {
            qDebug() << "Erreur de mise à jour : " << query.lastError().text();
        }
    } else {
        qDebug() << "Impossible d'ouvrir la base de données : " << QSqlDatabase::database().lastError().text();
    }
}





//estimation

std::vector<Matriel> Matriel::materielsDisponibles = {};

void Matriel::GM_initializeMateriels() {
    materielsDisponibles = {

                Matriel(1, "tracteur", "en bon état", 2500, "fonctionnel", 1),
                Matriel(2, "charrure", "en bon état", 80, "fonctionnel", 2),
                Matriel(3, "presse a balles", "en bon état", 2000, "fonctionnel", 3),
                Matriel(4, "Le rotoculteur", "en bon état", 40, "fonctionnel", 4),
                Matriel(5, "Capteurs de température et d'humidité de l'air", "en bon état", 50, "fonctionnel", 5),
                Matriel(6, "capteur de qualité de l'eau", "en bon état", 2500, "fonctionnel", 6),
                Matriel(7, "motoculteur", "en bon état", 12, "fonctionnel", 7),
                Matriel(8, "Semoir et épandeur d'engrais", "en bon état", 8000, "fonctionnel", 8),
                Matriel(9, "La moissonneuse-batteuse", "en bon état", 120, "fonctionnel", 9),
                Matriel(10, "La herse", "en bon état", 80, "fonctionnel", 10),
    };
}

double Matriel::getPrice(const QString& nom_mat) {
    for (const Matriel& materiel : materielsDisponibles) {
        if (materiel.getnom_mat() == nom_mat) {
            return materiel.getprix();
        }
    }

    // Gestion des matériaux non présents dans materielsDisponibles
    if (nom_mat == "tracteur") {
        return 2500.0;
    } else if (nom_mat == "charrue") {
        return 80.0;
    } else if (nom_mat == "presse a balles") {
        return 2000.0;
    } else if (nom_mat == "Le rotoculteur") {
        return 40.0;
    } else if (nom_mat == "Capteurs de température et d'humidité de l'air") {
        return 50.0;
    } else if (nom_mat == "Capteurs de qualité de l'eau") {
        return 2500.0;
    } else if (nom_mat == "motoculteur") {
        return 12.0;
    } else if (nom_mat == "Semoir et épandeur d'engrais") {
        return 8000.0;
    } else if (nom_mat == "La moissonneuse-batteuse") {
        return 120.0;
    } else if (nom_mat == "La herse") {
        return 80.0;
    }

    // Handle the case when nom_mat is not found
    return 0.0; // You can choose a default value or throw an exception depending on your requirements
}
