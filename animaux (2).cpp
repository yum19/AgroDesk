#include "animaux.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QDateTime>
#include "reminder.h"

Animaux::Animaux()
{
GA_id=0;GA_poids=0;
GA_type=" "; GA_sexe=" ";
GA_date_enter=" ";
GA_date_sortie=" ";
GA_dernier_vaccination=" "; GA_prochaine_vaccination=" ";
GA_malade=" ";

}
Animaux::Animaux(int GA_id,int GA_poids,QString GA_type,QString GA_sexe,QString GA_date_enter,QString GA_date_sortie,QString GA_dernier_vaccination,QString GA_prochaine_vaccination,QString GA_malade)
{
this->GA_id=GA_id; this->GA_poids=GA_poids;
this->GA_type=GA_type; this->GA_sexe=GA_sexe;
this->GA_date_enter=GA_date_enter;
this->GA_date_sortie=GA_date_sortie;
this->GA_dernier_vaccination=GA_dernier_vaccination;
this->GA_prochaine_vaccination=GA_prochaine_vaccination;
this->GA_malade=GA_malade;


}



int Animaux:: getGA_id() {return GA_id;}
int Animaux:: getGA_poids(){return GA_poids;}
QString Animaux:: getGA_type(){return GA_type;}
QString Animaux:: getGA_sexe(){return GA_sexe;}
QString Animaux:: getGA_date_enter(){return GA_date_enter;}
QString Animaux:: getGA_date_sortie(){return GA_date_sortie ;}
QString Animaux:: getGA_dernier_vaccination(){return GA_dernier_vaccination ;}
QString Animaux:: getGA_prochaine_vaccination(){return GA_prochaine_vaccination ;}
QString Animaux:: getGA_malade(){return GA_malade;}



void Animaux:: setGA_id(int GA_id){this->GA_id=GA_id;}
void Animaux:: setGA_poids(int GA_poids){this->GA_poids=GA_poids;}
void Animaux:: setGA_type(QString GA_type){this->GA_type=GA_type;}
void Animaux:: setGA_sexe(QString GA_sexe){this->GA_sexe=GA_sexe;}
void Animaux:: setGA_date_enter(QString GA_date_enter){this->GA_date_enter=GA_date_enter;}
void Animaux:: setGA_date_sortie(QString GA_date_sortie){this->GA_date_sortie=GA_date_sortie;}
void Animaux:: setGA_dernier_vaccination(QString GA_dernier_vaccination){this->GA_dernier_vaccination=GA_dernier_vaccination;}
void Animaux:: setGA_prochaine_vaccination(QString GA_prochaine_vaccination){this->GA_prochaine_vaccination=GA_prochaine_vaccination;}
void Animaux:: setGA_malade(QString GA_malade){this->GA_malade=GA_malade;}



QString Animaux::GA_getprochaine_vaccination() const {
    return GA_prochaine_vaccination;
}

QString Animaux::getGA_type() const {
    return GA_type;
}

int Animaux::getGA_id() const {
    return GA_id;
}



bool Animaux::GA_ajouter()
{

    QSqlQuery query;
    QString res= QString::number(GA_id);

    query.prepare("insert into ANIMAU (GA_id,GA_poids,GA_type,GA_sexe,GA_date_enter,GA_date_sortie,GA_dernier_vaccination,GA_prochaine_vaccination,GA_malade)""values(:GA_id,:GA_poids,:GA_type,:GA_sexe,:GA_date_enter,:GA_date_sortie,:GA_dernier_vaccination,:GA_prochaine_vaccination,:GA_malade)");

    query.bindValue(":GA_id",res);
    query.bindValue(":GA_poids",GA_poids);
    query.bindValue(":GA_type",GA_type);
    query.bindValue(":GA_sexe",GA_sexe);
    query.bindValue(":GA_date_enter",GA_date_enter);
    query.bindValue(":GA_date_sortie",GA_date_sortie);
    query.bindValue(":GA_dernier_vaccination",GA_dernier_vaccination);
    query.bindValue(":GA_prochaine_vaccination",GA_prochaine_vaccination);
    query.bindValue(":GA_malade",GA_malade);

return  query.exec();
}

QSqlQueryModel * Animaux::GA_afficher()
{
    {
        QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM ANIMAU");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("poids"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("sexe"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_enter"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_sortie"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("dernier_vaccination"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("prochaine_vaccination"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("malade"));


        return model;
    }
}





bool Animaux::GA_supprimer(int GA_id)
{


    QSqlQuery query;
    query.prepare("Delete from ANIMAU where GA_id= :GA_id");
    query.bindValue(0,GA_id);
    return query.exec();

}

bool Animaux::GA_modifier(int GA_id) {
    QSqlQuery query;
    QString res = QString::number(GA_id);

    query.prepare("UPDATE ANIMAU SET GA_poids = :GA_poids, GA_type = :GA_type, GA_sexe = :GA_sexe, GA_date_enter = :GA_date_enter, GA_date_sortie = :GA_date_sortie, GA_dernier_vaccination = :GA_dernier_vaccination, GA_prochaine_vaccination = :GA_prochaine_vaccination, GA_malade = :GA_malade WHERE GA_id = :GA_id");

    query.bindValue(":GA_id", res);
    query.bindValue(":GA_poids", GA_poids);
    query.bindValue(":GA_type", GA_type);
    query.bindValue(":GA_sexe", GA_sexe);
    query.bindValue(":GA_date_enter", GA_date_enter);
    query.bindValue(":GA_date_sortie", GA_date_sortie);
    query.bindValue(":GA_dernier_vaccination", GA_dernier_vaccination);
    query.bindValue(":GA_prochaine_vaccination", GA_prochaine_vaccination);
    query.bindValue(":GA_malade", GA_malade);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du dossier d'animaux:" << query.lastError().text();
        return false;
    }

    return true;
}


bool Animaux::GA_checkIfAnimalExists(int GA_id) {
    QSqlTableModel model;
    QSqlQuery query;
    model.setTable("animau");
    model.setFilter(QString("GA_id = %1").arg(GA_id));
    model.select();

    return model.rowCount() > 0;
    if (!query.exec()) {
      qDebug() << "Query Error: " << query.lastError().text();
        // Handle the error, return false or show an error message
        return false;
    }

    if (query.next()) {
           // Record found
           return true;
       } else {
           // No record found
           return false;
       }
}
bool Animaux::GA_isAnimalSick(int GA_id, QString &errorMessage) {
    // Check if the animal with the provided ID exists first
    if (!GA_checkIfAnimalExists(GA_id)) {
        errorMessage = "Animal introuvable dans la base de données";
        return false;
    }

    QSqlQuery query;

    // Prepare a SQL query to check if the animal with the provided ID is sick (malade = 'oui')
    query.prepare("SELECT GA_malade FROM animau WHERE GA_id = :GA_id");
    query.bindValue(":GA_id", GA_id);

    if (!query.exec()) {
        errorMessage = "Erreur de la base de données: " + query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString GA_malade = query.value(0).toString();
        return GA_malade.toLower() == "oui"; // Check if malade is "oui" (case-insensitive)
    }

    errorMessage = "Erreur inattendue lors de la vérification de l'état de santé de l'identifiant de l'animal ID";
    return false;
}



QList<Animaux> Animaux::GA_getAnimals()
{
    QList<Animaux> animals;
    QSqlQuery query;
    query.exec("SELECT GA_id, GA_prochaine_vaccination, GA_type FROM ANIMAU");

    while (query.next())
    {
        int GA_id = query.value(0).toInt();
        QString GA_prochaine_vaccination = query.value(1).toString();
        QString GA_type = query.value(2).toString();

        Animaux animal(GA_id, 0, GA_type, "", "", "", "", GA_prochaine_vaccination, "");
        animals.append(animal);
    }

    return animals;
}



QString Animaux::GA_calculateIllness(QComboBox* GA_comboBox1, QComboBox* GA_comboBox2, QComboBox* GA_comboBox3) {
    QString symptom1 = GA_comboBox1->currentText().trimmed().toLower();
    QString symptom2 = GA_comboBox2->currentText().trimmed().toLower();
    QString symptom3 = GA_comboBox3->currentText().trimmed().toLower();

    qDebug() << "Symptom 1: " << symptom1;
    qDebug() << "Symptom 2: " << symptom2;
    qDebug() << "Symptom 3: " << symptom3;

    if ((symptom1 != symptom2) && (symptom1 != symptom3) && (symptom2 != symptom3)) {
    // Check the combination of symptoms and return the associated sickness
            if ((symptom1 == "fièvre" || symptom1 == "aucun" || symptom1 == "aucun") &&
                    (symptom2 == "fièvre" || symptom2 == "aucun" || symptom2 == "aucun") &&
                    (symptom3 == "fièvre" || symptom3 == "aucun" || symptom3 == "aucun"))
            {
                return "Maladie probable : Grippe (influenza) 60%, Rhume 10%";


            } else if ((symptom1 == "perte d'appétit" || symptom1 == "aucun" || symptom1 == "aucun") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "aucun" || symptom2 == "aucun") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "aucun" || symptom3 == "aucun"))

            {
                return "Maladie probable : Maladie dentaire 40%, Infections virales ou bactériennes 40%.";

            } else if ((symptom1 == "difficulté respiratoire" || symptom1 == "aucun" || symptom1 == "aucun") &&
                       (symptom2 == "difficulté respiratoire" || symptom2 == "aucun" || symptom2 == "aucun") &&
                       (symptom3 == "difficulté respiratoire" || symptom3 == "aucun" || symptom3 == "aucun"))
            {
                return "Maladie probable : Pneumonie 30%, Asthme 20%, Infection respiratoire supérieure 30%.";

            } else if ((symptom1 == "écoulement nasal" || symptom1 == "aucun" || symptom1 == "aucun") &&
                       (symptom2 == "écoulement nasal" || symptom2 == "aucun" || symptom2 == "aucun") &&
                       (symptom3 == "écoulement nasal" || symptom3 == "aucun" || symptom3 == "aucun"))
            {
                return "Maladie probable : Infection respiratoire équine.";

            } else if ((symptom1 == "éternuements" || symptom1 == "aucun" || symptom1 == "aucun") &&
                       (symptom2 == "éternuements" || symptom2 == "aucun" || symptom2 == "aucun") &&
                       (symptom3 == "éternuements" || symptom3 == "aucun" || symptom3 == "aucun"))
            {
                return "Maladie probable : Rhume 20%, grippe aviaire 20%.";

            } else if ((symptom1 == "léthargie" || symptom1 == "aucun" || symptom1 == "aucun") &&
                        (symptom2 == "léthargie" || symptom2 == "aucun" || symptom2 == "aucun") &&
                        (symptom3 == "léthargie" || symptom3 == "aucun" || symptom3 == "aucun"))
            {
                return "Maladie probable : Infection parasitaire.";

            } else if ((symptom1 == "fièvre" || symptom1 == "perte d'appétit" || symptom1 == "aucun") &&
                       (symptom2 == "fièvre" || symptom2 == "perte d'appétit" || symptom2 == "aucun") &&
                       (symptom3 == "fièvre" || symptom3 == "perte d'appétit" || symptom3 == "aucun"))
            {
                return "Maladie probable : Infections bactériennes ou virales.";

            } else if ((symptom1 == "fièvre" || symptom1 == "difficulté respiratoire" || symptom1 == "aucun") &&
                       (symptom2 == "fièvre" || symptom2 == "difficulté respiratoire" || symptom2 == "aucun") &&
                       (symptom3 == "fièvre" || symptom3 == "difficulté respiratoire" || symptom3 == "aucun"))
            {
                return "Maladie probable : Maladie cardiaque 20%, Bronchite 30%.";

            } else if ((symptom1 == "fièvre" || symptom1 == "écoulement nasal" || symptom1 == "aucun") &&
                (symptom2 == "fièvre" || symptom2 == "écoulement nasale" || symptom2 == "aucun") &&
                (symptom3 == "fièvre" || symptom3 == "écoulement nasal" || symptom3 == "aucun"))
            {
                return "Maladie probable : Influenza aviaire.";

            } else if ((symptom1 == "fièvre" || symptom1 == "éternuements" || symptom1 == "aucun") &&
                       (symptom2 == "fièvre" || symptom2 == "éternuements" || symptom2 == "aucun") &&
                       (symptom3 == "fièvre" || symptom3 == "éternuements" || symptom3 == "aucun"))
            {
                return "Maladie probable : Grippe équine.";

            } else if ((symptom1 == "fièvre" || symptom1 == "léthargie" || symptom1 == "aucun") &&
                       (symptom2 == "fièvre" || symptom2 == "léthargie" || symptom2 == "aucun") &&
                       (symptom3 == "fièvre" || symptom3 == "léthargie" || symptom3 == "aucun"))
            {
                return "Maladie probable : Leptospirose.";

            } else if ((symptom1 == "perte d'appétit" || symptom1 == "difficulté respiratoire" || symptom1 == "aucun") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "difficulté respiratoire" || symptom2 == "aucun") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "difficulté respiratoire" || symptom3 == "aucun"))
            {
                return "Maladie probable : Insuffisance cardiaque congestive  40%, Allergies  30%,Tumeurs 20%.";

            } else if ((symptom1 == "perte d'appétit" || symptom1 == "éternuements" || symptom1 == "aucun") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "éternuements" || symptom2 == "aucun") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "éternuements" || symptom3 == "aucun"))
            {
                return "Maladie probable : Infections fongiques.";

            } else if ((symptom1 == "perte d'appétit" || symptom1 == "écoulement nasal" || symptom1 == "aucun") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "écoulement nasal" || symptom2 == "aucun") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "écoulement nasal" || symptom3 == "aucun"))
            {
                return "Maladie probable : Rhume 20% ou grippe canine/féline 5%.";

            } else if ((symptom1 == "perte d'appétit" || symptom1 == "léthargie" || symptom1 == "aucun") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "léthargie" || symptom2 == "aucun") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "léthargie" || symptom3 == "aucun"))
            {
                return "Maladie probable : Problèmes hépatiques.";


            } else if ((symptom1 == "difficulté respiratoire" || symptom1 == "écoulement nasal" || symptom1 == "aucun") &&
                       (symptom2 == "difficulté respiratoire" || symptom2 == "écoulement nasal" || symptom2 == "aucun") &&
                       (symptom3 == "difficulté respiratoire" || symptom3 == "écoulement nasal" || symptom3 == "aucun"))
            {
                return "Maladie probable : Rhume (Coryza) .";

            } else if ((symptom1 == "difficulté respiratoire" || symptom1 == "éternuements" || symptom1 == "aucun") &&
                       (symptom2 == "difficulté respiratoire" || symptom2 == "éternuements" || symptom2 == "aucun") &&
                       (symptom3 == "difficulté respiratoire" || symptom3 == "éternuements" || symptom3 == "aucun"))
            {
                return "Maladie probable : Allergies alimentaires 20% ou Pneumonie bactérienne ou virale 10%.";

            } else if ((symptom1 == "difficulté respiratoire" || symptom1 == "léthargie" || symptom1 == "aucun") &&
                       (symptom2 == "difficulté respiratoire" || symptom2 == "léthargie" || symptom2 == "aucun") &&
                       (symptom3 == "difficulté respiratoire" || symptom3 == "léthargie" || symptom3 == "aucun"))
            {
                return "Maladie probable : Anémie sévère.";


            }else if ((symptom1 == "écoulement nasal" || symptom1 == "éternuements" || symptom1 == "aucun") &&
                      (symptom2 == "écoulement nasal" || symptom2 == "éternuements" || symptom2 == "aucun") &&
                      (symptom3 == "écoulement nasal" || symptom3 == "éternuements" || symptom3 == "aucun"))
            {
                return "Maladie probable : Chlamydiose aviaire.";

            } else if ((symptom1 == "écoulement nasal" || symptom1 == "léthargie" || symptom1 == "aucun") &&
                       (symptom2 == "écoulement nasal" || symptom2 == "léthargie" || symptom2 == "aucun") &&
                       (symptom3 == "écoulement nasal" || symptom3 == "léthargie" || symptom3 == "aucun"))
            {
                return "Maladie probable : Influenza porcine 10%, Pasteurellose 30% .";

            }else if ((symptom1 == "éternuements" || symptom1 == "léthargie" || symptom1 == "aucun") &&
                      (symptom2 == "éternuements" || symptom2 == "léthargie" || symptom2 == "aucun") &&
                      (symptom3 == "éternuements" || symptom3 == "léthargie" || symptom3 == "aucun"))
            {
                return "Maladie probable : Maladie de Glässer .";

            }else if ((symptom1 == "fièvre" || symptom1 == "perte d'appétit" || symptom1 == "difficulté respiratoire") &&
                      (symptom2 == "fièvre" || symptom2 == "perte d'appétit" || symptom2 == "difficulté respiratoire") &&
                      (symptom3 == "fièvre" || symptom3 == "perte d'appétit" || symptom3 == "difficulté respiratoire"))
            {
                return "Maladie probable : Fièvre aphteuse 30%, Mycoplasma 20%, Maladie de Newcastle 5%.";

            } else if ((symptom1 == "fièvre" || symptom1 == "perte d'appétit" || symptom1 == "écoulement nasal") &&
                       (symptom2 == "fièvre" || symptom2 == "perte d'appétit" || symptom2 == "écoulement nasal") &&
                       (symptom3 == "fièvre" || symptom3 == "perte d'appétit" || symptom3 == "écoulement nasal"))
            {
                return "Maladie probable : Maladie de la langue bleue 50% .";

            } else if ((symptom1 == "fièvre" || symptom1 == "éternuements" || symptom1 == "écoulement nasal") &&
                       (symptom2 == "fièvre" || symptom2 == "éternuements" || symptom2 == "écoulement nasal") &&
                       (symptom3 == "fièvre" || symptom3 == "éternuements" || symptom3 == "écoulement nasal"))
            {
                return "Maladie probable : Chlamydiose aviaire.";




            }else if ((symptom1 == "fièvre" || symptom1 == "perte d'appétit" || symptom1 == "éternuements") &&
                      (symptom2 == "fièvre" || symptom2 == "perte d'appétit" || symptom2 == "éternuements") &&
                      (symptom3 == "fièvre" || symptom3 == "perte d'appétit" || symptom3 == "éternuements"))
            {
                return "Maladie probable : Mycoplasma hyopneumoniae  .";

            }else if ((symptom1 == "fièvre" || symptom1 == "difficulté respiratoire" || symptom1 == "léthargie") &&
                      (symptom2 == "fièvre" || symptom2 == "difficulté respiratoire" || symptom2 == "léthargie") &&
                      (symptom3 == "fièvre" || symptom3 == "difficulté respiratoire" || symptom3 == "léthargie"))
            {
                return "Maladie probable : La mammite 30%, Paratuberculose 20%  .";


            }else if ((symptom1 == "fièvre" || symptom1 == "difficulté respiratoire" || symptom1 == "éternuements") &&
                      (symptom2 == "fièvre" || symptom2 == "difficulté respiratoire" || symptom2 == "éternuements") &&
                      (symptom3 == "fièvre" || symptom3 == "difficulté respiratoire" || symptom3 == "éternuements"))
            {
                return "Maladie probable : La mammite 30%, Paratuberculose 20%  .";

            } else if ((symptom1 == "fièvre" || symptom1 == "difficulté respiratoire" || symptom1 == "écoulement nasal") &&
                       (symptom2 == "fièvre" || symptom2 == "difficulté respiratoire" || symptom2 == "écoulement nasal") &&
                       (symptom3 == "fièvre" || symptom3 == "difficulté respiratoire" || symptom3 == "écoulement nasal"))
            {
                return "Maladie probable : Maladie de la langue bleue 50% .";


            }else if ((symptom1 == "fièvre" || symptom1 == "perte d'appétit" || symptom1 == "léthargie") &&
                      (symptom2 == "fièvre" || symptom2 == "perte d'appétit" || symptom2 == "léthargie") &&
                      (symptom3 == "fièvre" || symptom3 == "perte d'appétit" || symptom3 == "léthargie"))
            {
                return "Maladie probable : La mammite 30%, Paratuberculose 20%  .";

            }else if ((symptom1 == "fièvre" || symptom1 == "écoulement nasal" || symptom1 == "léthargie") &&
                      (symptom2 == "fièvre" || symptom2 == "écoulement nasal" || symptom2 == "léthargie") &&
                      (symptom3 == "fièvre" || symptom3 == "écoulement nasal" || symptom3 == "léthargie"))
            {
                return "Maladie probable : La mammite 30%, Paratuberculose 10%  .";


            }else if ((symptom1 == "perte d'appétit" || symptom1 == "difficulté respiratoire" || symptom1 == "écoulement nasal") &&
                      (symptom2 == "perte d'appétit" || symptom2 == "difficulté respiratoire" || symptom2 == "écoulement nasal") &&
                      (symptom3 == "perte d'appétit" || symptom3 == "difficulté respiratoire" || symptom3 == "écoulement nasal"))
            {
                return "Maladie probable : Pasteurellose.";

            }else if ((symptom1 == "perte d'appétit" || symptom1 == "éternuements" || symptom1 == "écoulement nasal") &&
                      (symptom2 == "perte d'appétit" || symptom2 == "éternuements" || symptom2 == "écoulement nasal") &&
                      (symptom3 == "perte d'appétit" || symptom3 == "éternuements" || symptom3 == "écoulement nasal"))
            {
                return "Maladie probable : Maladie de la langue bleue 50% .";



            } else if ((symptom1 == "perte d'appétit" || symptom1 == "difficulté respiratoire" || symptom1 == "éternuements") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "difficulté respiratoire" || symptom2 == "éternuements") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "difficulté respiratoire" || symptom3 == "éternuements"))
            {
                return "Maladie probable : Bronchite infectieuse aviaire 30%, Fièvre aphteuse 20%.";

            } else if ((symptom1 == "perte d'appétit" || symptom1 == "léthargie" || symptom1 == "éternuements") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "léthargie" || symptom2 == "éternuements") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "léthargie" || symptom3 == "éternuements"))
            {
                return "Maladie probable : Maladie de Glässer .";

            } else if ((symptom1 == "perte d'appétit" || symptom1 == "difficulté respiratoire" || symptom1 == "léthargie") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "difficulté respiratoire" || symptom2 == "léthargie") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "difficulté respiratoire" || symptom3 == "léthargie"))
            {
                return "Maladie probable : Maladie de la vache folle.";

             }else if ((symptom1 == "perte d'appétit" || symptom1 == "écoulement nasal" || symptom1 == "léthargie") &&
                       (symptom2 == "perte d'appétit" || symptom2 == "écoulement nasal" || symptom2 == "léthargie") &&
                       (symptom3 == "perte d'appétit" || symptom3 == "écoulement nasal" || symptom3 == "léthargie"))
             {
                  return "Maladie probable : Fièvre aphteuse.";


            }else if ((symptom1 == "difficulté respiratoire" || symptom1 == "écoulement nasal" || symptom1 == "éternuements") &&
                      (symptom2 == "difficulté respiratoire" || symptom2 == "écoulement nasal" || symptom2 == "éternuements") &&
                      (symptom3 == "difficulté respiratoire" || symptom3 == "écoulement nasal" || symptom3 == "éternuements"))
            {
                return "Maladie probable : Rhinotrachéite infectieuse bovine ou Maladie d'Aujeszky.";

            } else if ((symptom1 == "difficulté respiratoire" || symptom1 == "écoulement nasal" || symptom1 == "léthargie") &&
                       (symptom2 == "difficulté respiratoire" || symptom2 == "écoulement nasal" || symptom2 == "léthargie") &&
                       (symptom3 == "difficulté respiratoire" || symptom3 == "écoulement nasal" || symptom3 == "léthargie"))
            {
                return "Maladie probable : Maladie respiratoire chronique.";


            } else if ((symptom1 == "difficulté respiratoire" || symptom1 == "éternuements" || symptom1 == "léthargie") &&
                       (symptom2 == "difficulté respiratoire" || symptom2 == "éternuements" || symptom2 == "léthargie") &&
                       (symptom3 == "difficulté respiratoire" || symptom3 == "éternuements" || symptom3 == "léthargie"))
            {
                return "Maladie probable : Maladie respiratoire chronique.";


            } else if ((symptom1 == "écoulement nasal" || symptom1 == "éternuements" || symptom1 == "léthargie") &&
                       (symptom2 == "écoulement nasal" || symptom2 == "éternuements" || symptom2 == "léthargie") &&
                       (symptom3 == "écoulement nasal" || symptom3 == "éternuements" || symptom3 == "léthargie"))
            {
                return "Maladie probable : Pasteurellose.";


            }


    // Add more debug information to help identify the issue
    qDebug() << "No matching sickness found for the selected symptoms.";
    qDebug() << "Debug Information - Symptom 1: " << symptom1;
    qDebug() << "Debug Information - Symptom 2: " << symptom2;
    qDebug() << "Debug Information - Symptom 3: " << symptom3;

    // If no matching combination is found, return an appropriate message
    return "Aucune maladie correspondante trouvée pour les symptômes sélectionnés.";

    } else {
            // If symptoms in different combo boxes are not distinct, return an appropriate message
            return "Veuillez choisir des symptômes distincts pour chaque catégorie.";
        }
}



