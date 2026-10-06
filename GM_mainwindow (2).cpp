#include "GM_mainwindow.h"
#include "ui_GM_mainwindow.h"
#include "matriel.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QDebug>
#include <QPdfWriter>
#include <QPageSize>
#include <QMarginsF>
#include <QPainter>
#include <QSqlQuery>
#include <QtPrintSupport/QPrinter>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QIntValidator>
#include <QPainter>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QAbstractAxis>
#include <QScriptEngine>

GM_mainwindow::GM_mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GM_mainwindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
        model->setColumnCount(2); // Deux colonnes pour Propriété et Valeur
       model->setHorizontalHeaderLabels(QStringList() << "Propriété" << "Valeur");

    ui->GM_tableViewaffiche->setModel(model);

        //connect(ui->GM_ajouter_clicked_mat, &QPushButton::clicked, this, &GM_mainwindow::on_ajouter_clicked_mat_clicked);
        connect(ui->GM_comboBoxmat, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePrice()));
        connect(ui->GM_comboBoxmat, SIGNAL(activated(const QString&)), this, SLOT(on_comboBox_activated(const QString&)));
        connect(ui->GM_doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onDoubleSpinBoxValueChanged(double)));
        connect(ui->GM_pushButton_vald, SIGNAL(clicked()), this, SLOT(on_pushButton_vald_clicked()));

        // Dans le constructeur ou l'initialisation
        connect(ui->GM_doubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                [=](double value) {
                    QString stringValue = QString::number(value);
                    int index = ui->GM_comboBoxmat->findText(stringValue);
                    if (index >= 0) {
                        ui->GM_comboBoxmat->setCurrentIndex(index);
                    }
                });

        // Définir la valeur maximale du QDoubleSpinBox
        ui->GM_doubleSpinBox->setMaximum(99.00);



        //connect(ui->GM_ajouterID, &QPushButton::clicked, this, &GM_mainwindow::on_ajouterID_clicked);


    ui->GM_tableViewaffiche->setModel(M.GM_afficher());
}

GM_mainwindow::~GM_mainwindow()
{
    delete ui;
}

void GM_mainwindow::on_GM_ajouter_clicked_mat_clicked()
{
    int id_mat=ui->GM_lineEdit_id->text().toInt();
    QString GM_nom_mat=ui->GM_lineEdit_nom->text();
    QString GM_etat=ui->GM_lineEdit_etat->text();
     double GM_prix=ui->GM_lineEdit_prix->text().toInt();
     QString GM_fonctionnalite=ui->GM_lineEdit_etat->text();
     int id_section=ui->GM_lineEdit_idsection->text().toInt();

        M.setid_mat( id_mat);
          M.setnom_mat(GM_nom_mat);
          M.setetat(GM_etat);
          M.setprix(GM_prix);
          M.setfonctionnalite(GM_fonctionnalite);
          M.setid_section(id_section);

        bool test = M.GM_ajouter();
        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\nCliquez sur Annuler pour quitter."),
                QMessageBox::Cancel);
        }
        /*else
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                QObject::tr("L'ajout a échoué."),
                QMessageBox::Ok);
        }*/
        ui->GM_tableViewaffiche->setModel(M1.GM_afficher());
}



void GM_mainwindow::on_GM_modifiermat_clicked()
{
    int id_mat=ui->GM_lineEdit_id->text().toInt();
    QString GM_nom_mat=ui->GM_lineEdit_nom->text();
    QString GM_etat=ui->GM_lineEdit_etat->text();
     int GM_prix=ui->GM_lineEdit_prix->text().toInt();
     QString GM_fonctionnalite=ui->GM_lineEdit_etat->text();
     int id_section=ui->GM_lineEdit_idsection->text().toInt();



     Matriel M(id_mat,GM_nom_mat,GM_etat,GM_prix,GM_fonctionnalite,id_section);
    bool test=M.GM_modifier(id_mat);
 ui->GM_tableViewaffiche->setModel(M.GM_afficher());
     if(test)
    {
         ui->GM_tableViewaffiche->setModel(M.GM_afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Update effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Update non effectué.\n"

                         "Click Cancel to exit."), QMessageBox::Cancel);
}



void GM_mainwindow::on_GM_supprimermat_clicked()
{
    int id_mat = ui->GM_lineEdit_supp->text().toInt();
        bool test = M1.GM_supprimer(id_mat);
        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("suppresion effectué\n""Click cancel to exit."),
                QMessageBox::Cancel);
            ui->GM_tableViewaffiche->setModel(M.GM_afficher());
            //EmptyTable();

        }
        else
        {
            QMessageBox::warning(nullptr, QObject::tr("not ok"),
                QObject::tr("supression non failed.\n""Click cancel to exit."),
                QMessageBox::Cancel);
        }
}



void GM_mainwindow::on_GM_cherchermat_clicked()
{
    int id_mat = ui->GM_lineEdit_cherch->text().toInt();
    if (id_mat != 0) {
        ui->GM_tableView_chercher->setModel(M.GM_recherche(id_mat));
    } else {
        ui->GM_tableView_chercher->setModel(M.GM_afficher());
    }
}



void GM_mainwindow::on_GM_trimat_clicked()
{
    ui->GM_tableView_chercher->setModel(M.GM_sort_tri_UP());

}

void GM_mainwindow::on_GM_tri_mat2_clicked()
{
    ui->GM_tableView_chercher->setModel(M.GM_sort_tri_DOWN());

}


void GM_mainwindow::on_GM_satistique_mat_clicked()
{
    // Créer un objet QChartView pour afficher le graphique
            QChartView *chartView = new QChartView(this);
            QChart *chart = new QChart();

            // Obtenir les statistiques du nombre de produit par cout et poids
            double GM_prix;

            QSqlQuery query;
            query.prepare("SELECT prix FROM MATERIEL");
            if (query.exec()) {
                while (query.next()) {
                   GM_prix = query.value("prix").toDouble();


                    // Créer une série de données pour chaque PRODUIT
                    QBarSeries *series = new QBarSeries();

                    QBarSet *setprix = new QBarSet("prix");
                    *setprix << GM_prix;
                    series->append(setprix);

                    // Ajouter la série au graphique
                    chart->addSeries(series);
                }
            } else {
                qDebug() << "Failed to execute query or retrieve data.";
                return;  // Exit the function if there's an issue with the query
            }

            // Créer l'axe des catégories
            QStringList categories;
            categories << "prix" ;
            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            chart->createDefaultAxes();
            chart->setAxisX(axisX, chart->series().at(0));

            // Créer le graphique à barres
            chartView->setChart(chart);

            // Afficher le graphique dans une nouvelle fenêtre
            QMainWindow *chartWindow = new QMainWindow(this);
            chartWindow->setCentralWidget(chartView);
            chartWindow->resize(800, 600);
            chartWindow->show();
}



void GM_mainwindow::on_GM_PDFexport_clicked()
{
    QString strStream;
                           QTextStream out(&strStream);

                            const int rowCount = ui->GM_tableViewaffiche->model()->rowCount();
                            const int columnCount = ui->GM_tableViewaffiche->model()->columnCount();
                           out <<  "<html>\n"
                           "<head>\n"
                                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                            <<  QString("<title>%1</title>\n").arg("strTitle")
                                            <<  "</head>\n"
                                            "<body bgcolor=#ffffff link=#5000A0>\n"

                                           //     "<align='right'> " << datefich << "</align>"
                                            "<center> <H1>Liste des produits</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                        // headers
                                        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                        out<<"<cellspacing=10 cellpadding=3>";
                                        for (int column = 0; column < columnCount; column++)
                                            if (!ui->GM_tableViewaffiche->isColumnHidden(column))
                                                out << QString("<th>%1</th>").arg(ui->GM_tableViewaffiche->model()->headerData(column, Qt::Horizontal).toString());
                                        out << "</tr></thead>\n";

                                        // data table
                                        for (int row = 0; row < rowCount; row++) {
                                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                            for (int column = 0; column < columnCount; column++) {
                                                if (!ui->GM_tableViewaffiche->isColumnHidden(column)) {
                                                    QString data = ui->GM_tableViewaffiche->model()->data(ui->GM_tableViewaffiche->model()->index(row, column)).toString().simplified();
                                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                }
                                            }
                                            out << "</tr>\n";
                                        }
                                        out <<  "</table> </center>\n"
                                            "</body>\n"
                                            "</html>\n";

                                  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                   QPrinter printer (QPrinter::PrinterResolution);
                                    printer.setOutputFormat(QPrinter::PdfFormat);
                                   printer.setPaperSize(QPrinter::A4);
                                  printer.setOutputFileName(fileName);

                                   QTextDocument doc;
                                    doc.setHtml(strStream);
                                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                    doc.print(&printer);

}








void GM_mainwindow::on_GM_ajouterID_clicked()
{
    int id_mat = ui->GM_lineEdit_idpanne->text().toInt();
       qDebug() << "ID à rechercher : " << id_mat;

       QString materiel = MaintenanceReparation::getMaterielEnPanne(id_mat);

       if (!materiel.isEmpty()) {
           // Ajouter les données du matériel en panne au modèle
           QStandardItemModel *model = new QStandardItemModel(2, 2, this);
           model->setItem(0, 0, new QStandardItem("ID du matériel:"));
           model->setItem(0, 1, new QStandardItem(QString::number(id_mat)));
           model->setItem(1, 0, new QStandardItem("Matériel en panne"));
           model->setItem(1, 1, new QStandardItem(materiel));

           // Lier le modèle à votre interface utilisateur
           ui->GM_tableView_maintennance->setModel(model);
       } else {
           QMessageBox::critical(this, "Erreur", "ID du matériel en panne introuvable.");
       }
}



void GM_mainwindow::on_GM_pushButton_oui_maintennance_clicked()
{
    QModelIndex index = ui->GM_tableView_maintennance->model()->index(0, 1);
        int id_mat = index.data().toInt();

        // Demander à l'utilisateur s'il veut réparer le matériel
        QMessageBox msgBox;
        msgBox.setText("Voulez-vous réparer ce matériel ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        int choix = msgBox.exec();

        if (choix == QMessageBox::Yes) {
            // Si l'utilisateur choisit "oui", réparer le matériel
            MaintenanceReparation::reparerMateriel(id_mat);
            QMessageBox::information(this, "Réparation réussie", "Le matériel a été réparé avec succès.");
        } else {
            // Si l'utilisateur choisit "non", annuler la réparation
            QMessageBox::information(this, "Annulation de la réparation", "La réparation a été annulée.");
        }

        ui->GM_tableView_chercher->setModel(nullptr);
}



void GM_mainwindow::on_GM_nonMaintenance_clicked()
{
    QMessageBox::information(this, "Annulation de la réparation", "La réparation a été annulée.");
        ui->GM_tableView_maintennance->setModel(nullptr);
}


void GM_mainwindow::on_GM_pushButton_vald_clicked()
{
    QString selectedMateriel = ui->GM_comboBoxmat->currentText();
            double prix = Matriel::getPrice(selectedMateriel);
            double budgetDisponible = ui->GM_doubleSpinBox->value();

            if (prix >= 0.0) {
                if (prix <= budgetDisponible) {
                    double newBudget = budgetDisponible - prix;

                    ui->GM_doubleSpinBox->setValue(newBudget);

                    QMessageBox::information(this, "Achat réussi", "Vous avez acheté " + selectedMateriel +
                                             ". Budget restant : " + QString::number(newBudget) + " EUR");

                 GM_updateBudgetProgressBar(newBudget);
                }
                    else
                    {
                    QMessageBox::warning(this, "Dépassement de budget", "Le coût du matériel dépasse votre budget disponible.");
                }
            } else {
                QMessageBox::warning(this, "Erreur", "Matériel non reconnu : " + selectedMateriel);
            }
}


void GM_mainwindow::on_GM_pushButton_annul_clicked()
{
    GM_updateBudgetProgressBar(GM_BUDGET_INITIAL);
        QMessageBox::information(this, "Annulation", "Vous avez annulé l'achat du matériel.");
        ui->GM_comboBoxmat->setCurrentIndex(-1); // Désélectionne tout dans la combobox
        ui->GM_lineEdit_pr->clear(); // Efface le prix affiché
}


const double GM_mainwindow::GM_BUDGET_INITIAL = 100000.0; // Initialisation de BUDGET_INITIAL avec la valeur de votre choix

void GM_mainwindow::GM_updateBudgetProgressBar(double budgetDisponible)
{
    // Assuming BUDGET_INITIAL is a member variable or constant initialized elsewhere
    const double GM_BUDGET_INITIAL = 100000.0;

    // Calculate the percentage of the budget used
    double pourcentageUtilise = 100 * (1 - (budgetDisponible / GM_BUDGET_INITIAL));

    // Set the progress bar value based on the calculated percentage
    ui->GM_progressBar->setValue(static_cast<int>(pourcentageUtilise));
}


void GM_mainwindow::GM_initializeMateriels() {
    // Initialise les matériels disponibles
    Matriel::GM_initializeMateriels();

    // Ajoute les éléments à la comboBox
    for (const Matriel& materiel : Matriel::materielsDisponibles) {
        ui->GM_comboBoxmat->addItem(materiel.getnom_mat() + " : " + QString::number(materiel.getprix()) + " EUR");
    }
}




void GM_mainwindow::on_GM_comboBoxmat_activated(const QString& selectedMaterial)
{
    // Récupérer le nom du matériel sélectionné depuis le comboBox
        QString materialName = selectedMaterial.split(" : ")[0]; // Séparer le nom du prix

        // Obtenir le prix correspondant au matériel sélectionné
        double materialPrice = Matriel::getPrice(materialName); // Utiliser votre méthode getPrice appropriée

        // Afficher le prix dans le QLineEdit (remplacer "lineEditPrice" par le nom de votre QLineEdit)
        ui->GM_lineEdit_pr->setText(QString::number(materialPrice)); // Afficher le prix dans un QLineEdit nommé "lineEditPrice"
}



void GM_mainwindow::on_GM_doubleSpinBox_textChanged(double nouveauBudget)
{
    // Liste de matériels disponibles avec leur prix
        std::vector<Matriel> materiels = {
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

        // Convertir la nouvelle valeur du doubleSpinBox en double
        // Utiliser la variable locale nommée 'nouveauBudget'
        ui->GM_comboBoxmat->clear(); // Effacer les éléments précédents

        for (const Matriel& materiel : materiels) {
            if (materiel.getprix() <= nouveauBudget) {
                ui->GM_comboBoxmat->addItem(materiel.getnom_mat() + " : " + QString::number(materiel.getprix()) + " EUR");
            }
        }
}



