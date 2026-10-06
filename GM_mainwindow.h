#ifndef GM_MAINWINDOW_H
#define GM_MAINWINDOW_H

#include <QMainWindow>
#include "matriel.h"
#include<QStandardItem>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <vector>
#include "animaux.h"
#include "ui_GA_mainwindow.h"

namespace Ui {
class GM_mainwindow;
}

class GM_mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GM_mainwindow(QWidget *parent = nullptr);
    ~GM_mainwindow();

    static std::vector<Matriel> materielsDisponibles;

private slots:




    /*void on_pushButton_oui_maintennance_clicked();

    void on_nonMaintenance_clicked();

    void on_listView_indexesMoved(const QModelIndexList &indexes);



  //  void on_comboBoxmateriel_activated(const QString &arg1);


    void afficherBoiteConfirmation(int id_mat);



    void on_PDFexport_clicked();

    void on_trimat_clicked();

    void on_cherchermat_clicked();



    void on_satistique_mat_clicked();


    void on_tri_mat2_clicked();




    void on_ajouter_clicked_mat_clicked();

    void on_supprimermat_clicked();

    void on_modifiermat_clicked();



        //void on_comboBox_activated(const QString &arg1);




        void on_ajouterID_clicked();

        void on_pushButton_annul_clicked();*/

      //  void on_doubleSpinBox_valueChanged(double arg1);
         // void on_comboBox_activated(const QString& selectedMaterial);

        //  void on_pushButton_vald_clicked();




          void on_GM_ajouter_clicked_mat_clicked();

          void on_GM_modifiermat_clicked();

          void on_GM_supprimermat_clicked();

          void on_GM_cherchermat_clicked();

          void on_GM_trimat_clicked();

          void on_GM_tri_mat2_clicked();

          void on_GM_satistique_mat_clicked();

          void on_GM_PDFexport_clicked();

          void on_GM_pushButton_vald_clicked();

          void on_GM_pushButton_annul_clicked();

          void on_GM_ajouterID_clicked();

          void on_GM_pushButton_oui_maintennance_clicked();

          void on_GM_nonMaintenance_clicked();

          void on_GM_doubleSpinBox_textChanged(double nouveauBudget);

          void on_GM_comboBoxmat_activated(const QString &arg1);

         // void on_GM_progressBar_valueChanged(int value);

private:
    Ui::GM_mainwindow *ui;
    Matriel M,M1;
    QStandardItemModel *model;
    /*static const double GM_BUDGET_INITIAL;


               void GM_updateBudgetProgressBar(double GM_budgetDisponible);
               void initializeMateriels();*/

    static const double GM_BUDGET_INITIAL;

    void GM_updateBudgetProgressBar(double GM_budgetDisponible);
    void GM_initializeMateriels();
};

#endif // GM_MAINWINDOW_H
