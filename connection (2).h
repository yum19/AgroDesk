#ifndef connection_h
#define connection_h
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>
#include <QSqlDatabase>
 class Connection
 {
     QSqlDatabase db;
 public:
     Connection();
     bool createconnect();
     void closeConnection();
 };

#endif // connexion_h
