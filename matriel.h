#ifndef MATRIEL_H
#define MATRIEL_H
#include <QString>
#include <QSqlQueryModel>



class MaintenanceReparation
{
public:
    static QString getMaterielEnPanne(int GM_id_mat);
    static void reparerMateriel(int GM_id_mat);
};
class Matriel
{

public:

    //Constructuers
    Matriel();
        Matriel(int,QString,QString,int,QString,int);
        QSqlQueryModel* GM_sort_tri_UP();
        QSqlQueryModel* GM_sort_tri_DOWN();

        Matriel(int GM_id, const QString& GM_nom, const QString& GM_etat, double GM_prix, const QString& GM_fonctionnalite, int GM_id_section);

        static void GM_initializeMateriels();


        static std::vector<Matriel> materielsDisponibles;





        //Getters
             int getid_mat();
             QString getnom_mat() ;
             QString getetat();
             double getprix() ;
             QString getfonctionnalite();
             int getid_section();



            //Setters
            void setid_mat(int);
            void setnom_mat(QString);
            void setetat(QString);
            void setprix(double);
            void setfonctionnalite(QString);
            void setid_section(int);


    bool GM_ajouter();
    QSqlQueryModel* GM_afficher();
    bool GM_supprimer(int);
    bool GM_modifier(int);

    QSqlQueryModel *model;
    QSqlQueryModel* GM_recherche(int id_mat);

    QSqlQueryModel* chercher_idMat(int id_mat);
    void GM_updateBudgetProgressBar(double GM_budgetDisponible);
     void on_pushButton_annulation_clicked();
     void on_GM_pushButton_annul_clicked();
     // static double getPrice(const QString &matriel);
    void on_doubleSpinBox_budget_textChanged(const QString &arg1);
     static double getPrice(const QString& nom_mat);
    QString getnom_mat() const
       {
           return nom_mat;
       }

       double getprix() const {
           return GM_prix;
       }



private:
       int id_mat,id_section;
       double GM_prix;
       QString nom_mat,GM_etat,GM_fonctionnalite;



};

#endif // MATRIEL_H
