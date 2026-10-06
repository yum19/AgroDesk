#include "mainwindow_gs.h"
#include "ui_mainwindow_gs.h"
#include "section.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>
#include <QObject>
#include <QTableView>
#include <QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QPdfWriter>
#include <QPainter>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QFile>
#include "arduino.h"
#include<QDebug>
#include <QSqlQuery>
#include <QTextCursor>


mainwindow_gs::mainwindow_gs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow_gs)
{
    // Create a separate QDialog object


    ui->setupUi(this);

    QRegExp regex("[A-Za-z]+"); // This regex allows only alphabetical characters
    QRegExpValidator *validator = new QRegExpValidator(regex, this);

    ui->lineEdit_nom_GS->setValidator(validator);
    ui->tableView_GS->setModel(c.GS_afficher());
    int ret=a.connect_arduino(); // lancer la connexion à arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
             QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
             //le slot update_label suite à la reception du signal readyRead (reception des données).

}

mainwindow_gs::~mainwindow_gs()
{
    delete ui;

}

#include <QTextTable>



void mainwindow_gs::on_displayTypeStatistics_4_GS_clicked()
{

    QString material = ui->lineEditMineralLevel_GS->text();
    double temperature = ui->lineEditTemperature_GS->text().toDouble();
    client c;
    QString planningMessage = c.GS_planCrop(material, temperature);
    QMessageBox::information(nullptr, QObject::tr("Crop Planning"), planningMessage, QMessageBox::Ok);
}

void mainwindow_gs::on_displayTypeStatistics_2_GS_clicked()
{
    client c;
        QMap<QString, int> surfaceCategories = c.GS_calculateSurfaceStatistics();

        if (!surfaceCategories.isEmpty()) {
            QString message = "Surface Statistics:\n\n";

            // Populate the message with data
            for (auto it = surfaceCategories.begin(); it != surfaceCategories.end(); ++it) {
                message += QString("%1: %2\n").arg(it.key()).arg(it.value());
            }

            QMessageBox::information(nullptr, QObject::tr("Surface Statistics"), message, QMessageBox::Ok);
        } else {
            QMessageBox::warning(nullptr, QObject::tr("Avertissement"),
                                 QObject::tr("Aucun enregistrement trouvé pour calculer les statistiques."),
                                 QMessageBox::Ok);
        }
}

/*void MainWindow::on_displayTypeStatistics_GS_clicked()
{
    client c;
        QMap<QString, double> typePercentages = c.GS_calculateTypePercentage();

        if (!typePercentages.isEmpty()) {
            QString message = "Statistics:\n\n";

            for (auto it = typePercentages.begin(); it != typePercentages.end(); ++it) {
                message += QString("Type: %1, Percentage: %2%\n").arg(it.key()).arg(it.value(), 0, 'f', 2);
            }

            QMessageBox::information(nullptr, QObject::tr("Statistics"), message, QMessageBox::Ok);
        } else {
            QMessageBox::warning(nullptr, QObject::tr("Avertissement"),
                                 QObject::tr("Aucun enregistrement trouvé pour calculer les pourcentages."),
                                 QMessageBox::Ok);
        }
}*/
void mainwindow_gs::on_displayTypeStatistics_GS_clicked()
{
    // Créer un objet QChartView pour afficher le graphique

    // Obtenir les statistiques du Montant par type de design à partir de la base de données
    QMap<QString, double> temperatureMap;

    QSqlQuery query;
    query.prepare("SELECT GS_type, AVG(GS_temperature) FROM client GROUP BY GS_type");

    if (query.exec()) {
        while (query.next()) {
            QString type = query.value(0).toString();
            double avgTemperature = query.value(1).toDouble();
            temperatureMap[type] = avgTemperature;  // Ajout des résultats à temperatureMap
            qDebug() << "type " << type << ", avgTemperature " << avgTemperature;
        }
    }

    // Calculer la température moyenne pour chaque type
    double totalTemperature = 0.0;
    for (double avgTemperature : temperatureMap.values()) {
        totalTemperature += avgTemperature;
    }

    // Afficher la température moyenne pour chaque type
    for (const QString &type : temperatureMap.keys()) {
        qDebug() << "avgTemperature " << type << ": " << temperatureMap[type];
    }

    // Créer une série de données pour le graphique circulaire
    QPieSeries *series = new QPieSeries();

    // Ajouter les tranches au graphique et calculer les pourcentages
    for (const QString &type : temperatureMap.keys()) {
        QPieSlice *slice = series->append(type, temperatureMap[type]);

        // Calculer le pourcentage en fonction de la température totale
        if (totalTemperature != 0.0) {
            slice->setLabel(QString("%1\n%2%").arg(type).arg((temperatureMap[type] / totalTemperature) * 100, 0, 'f', 1));
        } else {
            // Gérer le cas où totalTemperature est égal à zéro (éviter la division par zéro)
            slice->setLabel(QString("%1\n0%").arg(type));
        }
    }

    // Ajouter la série au graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Statistique de température par type de client");
    // Créer le graphique circulaire
    QChartView *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

    // Définir le thème du graphique
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    // Afficher le graphique dans une nouvelle fenêtre
    QMainWindow *chartWindow = new QMainWindow(this);
    chartWindow->setCentralWidget(chartView);
    chartWindow->resize(800, 600);
    chartWindow->show();
}


void mainwindow_gs::on_trier_GS_clicked()
{
    QString attributToSort = ui->comboBoxAttribut_2_GS->currentText(); // Get the selected attribute to sort

        bool isNumeric = (attributToSort == "surface"); // Check if the attribute is "surface"

        client c;
        QSqlQueryModel *sortedModel = c.GS_trierParAttribut(attributToSort, isNumeric);

        if (sortedModel) {
            ui->tableView_GS->setModel(sortedModel);
            ui->tableView_GS->resizeColumnsToContents();  // Optionally adjust column widths
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Erreur lors du tri des données.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void mainwindow_gs::on_pdf_2_GS_clicked()
{
    client c;
    QSqlQueryModel *dataModel = c.GS_getAllData();

    if (!dataModel) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Erreur lors de la récupération des données pour le PDF."),
                              QMessageBox::Cancel);
        return;
    }

    QTextDocument doc;

    QTextCursor cursor(&doc);
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    QTextTable *table = cursor.insertTable(dataModel->rowCount() + 1, dataModel->columnCount(), tableFormat);


    for (int col = 0; col < dataModel->columnCount(); ++col) {
        table->cellAt(0, col).firstCursorPosition().insertText(dataModel->headerData(col, Qt::Horizontal).toString());
    }


    for (int row = 0; row < dataModel->rowCount(); ++row) {
        for (int col = 0; col < dataModel->columnCount(); ++col) {
            table->cellAt(row + 1, col).firstCursorPosition().insertText(dataModel->data(dataModel->index(row, col)).toString());
        }
    }

    // Save the PDF file
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf)"));

    if (!filePath.isEmpty()) {
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);

        doc.print(&printer);

        if (printer.Error) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Erreur lors de l'impression du fichier PDF."),
                                  QMessageBox::Cancel);
        }
    }

    delete dataModel; // Don't forget to release the memory

}

void mainwindow_gs::on_chercher_2_GS_clicked()
{
    QString valeurToSearch = ui->lineEditSearch_GS->text(); // Get the search value

    client c;
    bool found = c.GS_chercher(valeurToSearch);

    if (found) {
        QMessageBox::information(nullptr, QObject::tr("Résultat de la recherche"),
                                 QObject::tr("La valeur a été trouvée dans la base de données."),
                                 QMessageBox::Ok);
    } else {
        QMessageBox::information(nullptr, QObject::tr("Résultat de la recherche"),
                                 QObject::tr("La valeur n'a pas été trouvée dans la base de données."),
                                 QMessageBox::Ok);
    }
}

void mainwindow_gs::on_modifier_2_GS_clicked()
{
    // Retrieve input values from UI
    QString nom = ui->lineEdit_nom_3_GS->text();
    QString type = ui->lineEdit_type_3_GS->text();
    QString surface = ui->lineEdit_surface_3_GS->text();
    double temperature = ui->lineEdit_temperature_3_GS->text().toDouble();
    double mineralLevel = ui->lineEdit_mineralLevel_3_GS->text().toDouble();


    // Create an instance of the client class
    client c;
    c.setGS_nom(nom);
    c.setGS_surface(surface);
    c.setGS_type(type);
    c.GS_setTemperature(temperature);
    c.GS_setMineralLevel(mineralLevel);


    // Try to update the record
    bool test = c.GS_modifier(nom);

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Update effectué.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_GS->setModel(c.GS_afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("Update non effectué.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void mainwindow_gs::on_pushButton_3_GS_clicked()
{
    client c1;
    c1.setGS_nom(ui->lineEdit_nom_supp_2_GS->text());
    bool test=c1.GS_supprimer(c1.getGS_nom());// win taayet lel butoon clicked


    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Supprimer effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_GS->setModel(c.GS_afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Supprimer non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void mainwindow_gs::on_ajouter_GS_clicked()
{
    // Retrieve input values from UI
    QString nom = ui->lineEdit_nom_GS->text();
    QString type = ui->lineEdit_type_GS->text();
    QString surface = ui->lineEdit_surface_GS->text();
    double temperature = ui->lineEdit_temperature_GS->text().toDouble();
    double mineralLevel = ui->lineEdit_mineralLevel_GS->text().toDouble();

    // Create an instance of the client class with mineralLevel and temperature
    client c(nom, surface, type, temperature, mineralLevel);

    // Try to add the record
    bool test = c.GS_ajouter();

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Ajout effectué.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_GS->setModel(c.GS_afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("Ajout non effectué.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void mainwindow_gs::on_tableView_GS_activated(const QModelIndex &index)
{
    QString val=ui->tableView_GS->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from section where nom='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_nom_GS->setText(qry.value(2).toString());
                ui->lineEdit_surface_GS->setText(qry.value(0).toString());
                ui->lineEdit_type_GS->setText(qry.value(3).toString());
            }
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("selection n'est pas effuctué"),
                                  QObject::tr("connection failed.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void mainwindow_gs::on_pushButton_GS_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT MINERALLEVEL FROM section ");

    if (query.exec())
    {
        if (query.next())
        {
            int MINERALLEVEL = query.value("MINERALLEVEL").toInt();
            data.append(QString::number(MINERALLEVEL));

            // Debug statement
            qDebug() << "Sending to Arduino: " << data;

            a.write_to_arduino(data);
        }
        else
        {
            qDebug() << "No data found in the 'section' table.";
        }
    }
    else
    {
        qDebug() << "Query execution failed:" << query.lastError().text();
    }

}
