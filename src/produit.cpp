#include "produit.h"
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QInputDialog>
#include<QFile>
#include<QDateTime>
Produit::Produit()
{
    gpnom="";gpref=0;gpprix=0;
    gpdate_produit="";
    gpnbr_produits=0;gppoids=0;
}
Produit::Produit(QString gpnom,int gpref,int gpprix,QString gpdate_produit,int gpnbr_produits,int gppoids)
{
    this->gpnom = gpnom;
    this->gpref = gpref;
    this->gpprix = gpprix;
    this->gpdate_produit = gpdate_produit;
    this->gpnbr_produits=gpnbr_produits;
    this->gppoids=gppoids;

}
/*bool Produit::loadFromDatabase() {
    QSqlDatabase db = QSqlDatabase::database();  // Use the existing database connection

    if (!db.isOpen()) {
        // Handle database connection error
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT gpnom, gpprix, nbr_produit FROM PRODUIT WHERE gpnom = :gpnom");
    query.bindValue(":gpnom", gpnom);

    if (query.exec() && query.next()) {
        gpnom = query.value("gpnom").toString();
        gpprix = query.value("gpprix").toDouble();
        gpnbr_produits = query.value("gpnbr_produits").toInt();
        return true;
    } else {
        // Handle database query error
        return false;
    }
}*/
bool Produit::ajouter()

{
    QSqlQuery query;
    QString res = QString::number(gpref);

    query.prepare("INSERT INTO  PRODUIT (gpnom, gpref,gpprix,gpdate_produit,gpnbr_produits,gppoids) VALUES (:gpnom, :gpref, :gpprix,:gpdate_produit,:gpnbr_produits,:gppoids)");
    query.bindValue(":gpnom",gpnom);
    query.bindValue(":gpref", res);
    query.bindValue(":gpprix", gpprix);
    query.bindValue(":gpdate_produit",gpdate_produit);
    query.bindValue(":gpnbr_produits", gpnbr_produits);
    query.bindValue(":gppoids", gppoids);
    QString actionDetails = "reference: " + QString::number(gpref) ;
                                    /*", Entreprise: " + entreprise +
                                    ", Objet: " + objet +
                                    ", Type: " + type +
                                    ", Contact: " + QString::number(contact) +
                                    ", Email: " + Email +
                                    ", Date: " + date.toString("yyyy-MM-dd")  +
                                    ", Etat: " + etat;*/

            // Log the action
            logAction("produit ajoutée", actionDetails);
    return (query.exec());
}
QSqlQueryModel * Produit:: afficher()
{
 QSqlQueryModel *model=new QSqlQueryModel();
 model->setQuery("SELECT * FROM PRODUIT");
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("gpnom"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("gpref"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("gpprix"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("gpdate_produits"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("gpnbr_produits"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("gppoids"));
 return model;
}
bool Produit::supprimer(int gpref)
{
QSqlQuery query;
QString res = QString::number(gpref);
query.prepare("DELETE FROM PRODUIT WHERE gpref=:gpref");
query.bindValue(":gpref",res);
QString actionDetails = "Reference: " + QString::number(gpref) ;
                                /*", Entreprise: " + entreprise +
                                ", Objet: " + objet +
                                ", Type: " + type +
                                ", Contact: " + QString::number(contact) +
                                ", Email: " + Email +
                                ", Date: " + date.toString("yyyy-MM-dd")  +
                                ", Etat: " + etat;*/

        // Log the action
        logAction("produit supprimer", actionDetails);
return query.exec();
}
bool Produit::modifier(int gpref)
{
    QSqlQuery query;
    QString res = QString::number(gpref);
    query.prepare("UPDATE PRODUIT SET gpnom = :gpnom, gpref = :gpref, gpprix = :gpprix, gpdate_produit = :gpdate_produit,gpnbr_produits=:gpnbr_produits,gppoids=:gppoids");
    query.bindValue(":gpnom",gpnom);
    query.bindValue(":gpref", res);
    query.bindValue(":gpprix", gpprix);
    query.bindValue(":gpdate_produit",gpdate_produit);
    query.bindValue(":gpnbr_produits", gpnbr_produits);
    query.bindValue(":gppoids", gppoids);
    QString actionDetails = "Reference: " + QString::number(gpref) ;
                                    /*", Entreprise: " + entreprise +
                                    ", Objet: " + objet +
                                    ", Type: " + type +
                                    ", Contact: " + QString::number(contact) +
                                    ", Email: " + Email +
                                    ", Date: " + date.toString("yyyy-MM-dd")  +
                                    ", Etat: " + etat;*/

            // Log the action
            logAction("produit modifier", actionDetails);
 return query.exec();
}
QSqlQueryModel* Produit::rechercherpargpnom ( QString le_rechercher)
{
    QSqlQueryModel* queryModel = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUIT WHERE gpnom = :gpnom");
    query.bindValue(":gpnom", le_rechercher);

    if (query.exec())
    {
       queryModel->setQuery(query);
        return queryModel;
    }

    // En cas d'erreur, retournez un modèle vide
    delete queryModel;
    return nullptr;
}
/*bool Produit::sell() {
    int quantityToSell;
    // You need to obtain the quantity to sell from your UI or another source
    // For example, you can use a dialog or a QLineEdit to get user input.

    // Validate input
    bool ok;
    quantityToSell = QInputDialog::getInt(nullptr, "Sell Product", "Enter quantity to sell:", 1, 1, gpnbr_produits, 1, &ok);

    if (!ok || quantityToSell <= 0) {
        qDebug() << "Invalid quantity to sell";
        return false;
    }

    if (quantityToSell <= gpnbr_produits) {
        // Subtract the sold quantity from existing quantity
        gpnbr_produits -= quantityToSell;

        // Update the database with the new quantity
        QSqlQuery query;
        query.prepare("UPDATE PRODUIT SET gpnbr_produits = :quantity WHERE gpref = :gpref");
        query.bindValue(":quantity", gpnbr_produits);
        query.bindValue(":gpref", gpref);

        if (query.exec()) {
            return true;  // Sale successful
        } else {
            qDebug() << "Failed to update database with new quantity";
            // You might want to handle this error condition
            return false;
        }
    } else {
        qDebug() << "Not enough quantity in stock.";
        return false;
    }
}*/
void Produit::logAction(const QString& actionType, const QString& actionDetails)
{

    QFile logFile("actions.log");
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);

               out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << " ";
               out << actionType << " ";
               out << actionDetails.left(25) << "\n";
               out.flush();

        logFile.close();
     qDebug() << "Action logged:" << actionDetails;  // Add this line for debug output
    }
 else {
    qDebug() << "Error opening the log file for writing:" << logFile.errorString();
}
}



