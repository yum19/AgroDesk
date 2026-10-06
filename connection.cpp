#include "connection.h"
#include<QDebug>

Connection::Connection() {}
bool Connection::createconnect()
{
    db=QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("ahmed03");//inserer nom de l'utilisateur
    db.setPassword("ahmed03");//inserer mot de passe de cet utilisateur
    if(db.open()) test=true;
    return test;
    if (!db.open()) {
    qDebug() << "Database Error: " << db.lastError().text();
        // Handle the error, return false or show an error message
        return false;
    }
}

void Connection::closeConnection()
{db.close();}
