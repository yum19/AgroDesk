#ifndef PRODUIT_H
#define PRODUIT_H
#include<QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
class Produit
{
public:
    Produit();
    int  gpprix ,gpnbr_produits;
    Produit(QString gpnom,int gpref,int gpprix,QString gpdate_produit ,int gpnbr_produit,int gppoids);
    QString getgpnom(){return gpnom;};
    int getgpref(){return gpref;}
    //int getquantitySold(){return quantitySold;}
    int getgpprix(){return gpprix;}
    QString getgpdate_produit(){return gpdate_produit;}
    int getgpnbr_produits(){return gpnbr_produits;}
    int getgppoids(){return gppoids;}

    void setgpnom(QString n){gpnom=n;}
    void setgpref(int r){gpref=r;}
   // void setquantitySold(int qs){quantitySold=qs;}
    void setgpprix(int p){gpprix=p;}
    void setgpdate_produit(QString dp){gpdate_produit=dp;}
    void  setgpnbr_produits(int np){gpnbr_produits=np;}
    void setgppoids(int nd){gppoids=nd;}

   // bool loadFromDatabase();
    bool ajouter();
    void logAction(const QString& actionType, const QString& actionDetails);
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* rechercherpargpnom ( QString le_rechercher);
   // bool sell();


private:
    QString gpnom;
    //int quantitySold;
    int gpref;
    int gppoids;
    QString gpdate_produit  ;

};

#endif // PRODUIT_H
