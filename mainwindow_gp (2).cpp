#include "mainwindow_gp.h"
#include "ui_mainwindow_gp.h"
#include"produit.h"
#include"connection.h"
#include<QMessageBox>
#include<QApplication>
#include <QValidator>
#include <QIntValidator>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QPainter>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QtCharts/QPieSeries>
#include <QSortFilterProxyModel>
#include <QtPrintSupport/QPrinter>
#include<QtWidgets>
#include <QSqlRecord>
#include <QtCharts>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QWidget>
#include <QtSql>
#include<QPieSlice>
#include <QMap>
#include<QDate>
#include <QDateTime>
#include <QComboBox>
#include <QSpinBox>
#include"arduino.h"
MainWindow_gp::MainWindow_gp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow_gp)
{
    ui->setupUi(this);
    ui->tableView_gp->setModel(Etmp.afficher());
    connect(ui->sellproduct, SIGNAL(clicked()), this, SLOT(sellProduct()));

    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).

}

MainWindow_gp::~MainWindow_gp()
{
    delete ui;

}

void MainWindow_gp::on_ajouter_gp_clicked()
{   QString gpnom=ui->le_nom_gp->text();
    int gpref=ui->le_ref_gp->text().toInt();
    int gpprix=ui->le_prix_gp->text().toInt();
    QString gpdate_produit=ui->le_date_gp->text();
    int gpnbr_produits=ui->le_nbr_gp->text().toInt();
    int gppoids=ui->le_poids_gp->text().toInt();
    Produit p(gpnom,gpref,gpprix,gpdate_produit,gpnbr_produits,gppoids);
    bool test=p.ajouter();
  if(test)
  {
  QMessageBox::information(nullptr,QObject::tr("ok"),
  QObject::tr("ajout effectué\n""Click cancel to exit."),
  QMessageBox::Cancel);
 }
  else
  {
      QMessageBox::critical(nullptr,QObject::tr("not OK"),
      QObject::tr("ajout non effectué.\n""Click Cancel to exit."),
      QMessageBox::Cancel);
}
 ui->tableView_gp->setModel(Etmp.afficher());
}

void MainWindow_gp::on_quitter_gp_clicked()
{
   QCoreApplication::quit();  // This will exit the application
}

/*void MainWindow::on_radioButton_2_clicked()
{
    QSqlQueryModel *originalModel = Etmp.afficher();

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(originalModel);
    proxyModel->setSortRole(Qt::DisplayRole);  // Set the sort role to DisplayRole

    proxyModel->sort(0, Qt::AscendingOrder);

    ui->tableView_gp->setModel(proxyModel);
}*/

void MainWindow_gp::on_modifier_gp_clicked()
{
    QString gpnom=ui->le_nom_gp->text();
      int gpref=ui->le_ref_gp->text().toInt();
      int gpprix=ui->le_prix_gp->text().toInt();
      QString gpdate_produit=ui->le_date_gp->text();
      int gpnbr_produits=ui->le_nbr_gp->text().toInt();
      int gppoids=ui->le_poids_gp->text().toInt();

    Produit p(gpnom,gpref,gpprix,gpdate_produit,gpnbr_produits,gppoids);
    bool test=p.modifier(gpref);
     ui->tableView_gp->setModel(Etmp.afficher());
    if(test)
    {

    QMessageBox::information(nullptr,QObject::tr("ok"),
    QObject::tr("modifier effectué\n""Click cancel to exit."),
    QMessageBox::Cancel);
   }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
        QObject::tr("modifier non effectué.\n""Click Cancel to exit."),
        QMessageBox::Cancel);
  }
  }

void MainWindow_gp::on_pushButton_gp_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug() << dir;

    QPdfWriter pdf(dir + "/PdfList.pdf");
    QPainter painter(&pdf);

    int i = 4000;
    int page = 1; // Initialize the page number to 1

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(230, 230, 230, 100)); // very light gray color with alpha transparency
    painter.drawRect(QRectF(10000, 500, 100, 200)); // change the coordinates and size to fit your needs

    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.setPen(Qt::blue);
    painter.drawText(QRectF(200, 500, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "ADS : AGRODESK");
    painter.setPen(QPen(Qt::black, 2)); // set pen color and width
    painter.drawLine(QPointF(100, 800), QPointF(9200, 800)); // draw a line from (200,550) to (10000,550)
    painter.setFont(QFont("Arial", 11));
    painter.setPen(Qt::black);

    painter.drawText(QRectF(200, 900, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "PDF generated in: " + QDateTime::currentDateTime().toString());

    painter.setFont(QFont("Arial", 11));
    painter.drawText(QRectF(7000, 2100, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "Page: " + QString::number(page));

    painter.setFont(QFont("Arial", 11));
    painter.drawText(QRectF(200, 1500, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "PDF Number: " + QString::number(QDateTime::currentDateTime().toTime_t()));

    painter.setFont(QFont("Arial", 11));
    painter.drawText(QRectF(200, 1800, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "object of PDF file: to list Produits");

    painter.setFont(QFont("Arial", 11));
    painter.drawText(QRectF(200, 1200, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "local: tunis, ariana");

    painter.setFont(QFont("Arial", 11));
    painter.drawText(QRectF(200, 2100, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "email: AGRODESKSTUDIO@gmail.com");

    QSqlQuery countQuery;
    countQuery.prepare("SELECT COUNT(*) as produit_count FROM PRODUIT"); // Assuming your table name is Produits
    countQuery.exec();

    if (countQuery.next()) {
        int produitCount = countQuery.value("produit_count").toInt();
        // perform calculation using produitCount here

        // draw produit count on painter object
        painter.setFont(QFont("Arial", 11));
        painter.drawText(QRectF(7000, 1800, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "Total Produits: " + QString::number(produitCount));
    }

    painter.setFont(QFont("Arial", 13, QFont::Bold));
    painter.setPen(Qt::blue);
    painter.drawText(QRectF(4000, 2400, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "list of Produits");

    painter.setPen(Qt::black);
    QColor gray(220, 220, 220);
    painter.setFont(QFont("Arial", 15));

    painter.drawRect(100, 3000, 9400, 500);
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(300, 3300, "gpnom");
    painter.drawText(2700, 3300, "gpref");
    painter.drawText(5400, 3300, "prix");
    painter.drawText(7400, 3300, "date_produit");
    painter.drawText(7400, 3300, "nbr_produits");
    painter.drawText(7400, 3300, "poids");
    painter.drawRect(100, 3000, 9400, 10700);

    QTextDocument previewDoc;
    QTextCursor cursor(&previewDoc);
    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUIT ORDER BY gpref "); // Assuming your table name is Produits and id column is idP
    query.exec();

    while (query.next())
    {
        if (i > 14000) {
            pdf.newPage();
            i = 4000;
            page++;
            painter.setFont(QFont("Arial", 12, QFont::Bold));
            painter.setPen(Qt::blue);
            painter.drawText(QRectF(200, 500, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "AD : AGRODEK");
            painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(QPointF(100, 800), QPointF(9200, 800));
            painter.setFont(QFont("Arial", 11));
            painter.setPen(Qt::black);
            painter.drawText(QRectF(200, 900, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "PDF generated in: " + QDateTime::currentDateTime().toString());

            painter.setFont(QFont("Arial", 11));
            painter.drawText(QRectF(7000, 2100, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "Page: " + QString::number(page));

            painter.setFont(QFont("Arial", 11));
            painter.drawText(QRectF(200, 1500, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "PDF Number: " + QString::number(QDateTime::currentDateTime().toTime_t()));

            painter.setFont(QFont("Arial", 11));
            painter.drawText(QRectF(200, 1800, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "object of PDF file: to list Produits");
            painter.setFont(QFont("Arial", 11));
            painter.drawText(QRectF(200, 1200, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "local: Tunis, Ariana");

            painter.setFont(QFont("Arial", 11));
            painter.drawText(QRectF(200, 2100, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "email: AGRODESKSTUDIO@gmail.com");

            QSqlQuery countQuery;
            countQuery.prepare("SELECT COUNT(*) as produit_count FROM Produits");
            countQuery.exec();

            if (countQuery.next()) {
                int produitCount = countQuery.value("produit_count").toInt();
                // perform calculation using produitCount here

                // draw produit count on painter object
                painter.setFont(QFont("Arial", 11));
                painter.drawText(QRectF(7000, 1800, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "Total Produits: " + QString::number(produitCount));
            }

            painter.setFont(QFont("Arial", 13, QFont::Bold));
            painter.setPen(Qt::blue);
            painter.drawText(QRectF(4000, 2400, 9000, 200), Qt::AlignLeft | Qt::AlignTop, "list of Produits");

            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 11));

            painter.drawRect(100, 3000, 9400, 500);
            painter.setFont(QFont("Arial", 10, QFont::Bold));
            painter.drawText(300, 3300, "gpnom");
            painter.drawText(2700, 3300, "gpref");
            painter.drawText(5400, 3300, "prix");
            painter.drawText(7400, 3300, "date_produit");
            painter.drawText(7400, 3300, "nbr_produits");
            painter.drawText(7400, 3300, "poids");
            painter.drawRect(100, 3000, 9400, 10700);
        }

        painter.setFont(QFont("Arial", 10));
        painter.drawText(300, i, query.value(0).toString());
        painter.drawText(2700, i, query.value(1).toString());
        painter.drawText(5400, i, query.value(2).toString());
        painter.drawText(7400, i, query.value(3).toString());
        painter.drawText(7500, i, query.value(4).toString());
        painter.drawText(7500, i, query.value(4).toString());
        painter.drawText(7500, i, query.value(4).toString());

        i = i + 500;
    }

    int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                        QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir + "/PdfList.pdf"));

        painter.end();
    }
    else
    {
        painter.end();
    }
}

void MainWindow_gp::on_pb_recherche_gp_clicked()
{
    QString gpnom_Recherche = ui->le_recherche_gp->text();

       Produit p;
       QSqlQueryModel* resultat = p.rechercherpargpnom(gpnom_Recherche );

       if (resultat->rowCount() > 0)
       {
           ui->tableView_recherche_gp->setModel(resultat);
           QMessageBox::information(nullptr, QObject::tr("Succès"),
               QObject::tr("Recherche effectuée\n"
                           "Cliquez sur Annuler pour fermer."), QMessageBox::Cancel);
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
               QObject::tr("Recherche non effectuée\n"
                           "Cliquez sur Annuler pour fermer."), QMessageBox::Cancel);
       }
   }

void MainWindow_gp::on_supprimer_gp_clicked()
{
    int gpref =ui->supp_ref_gp->text().toInt();
    bool test=Etmp.supprimer(gpref);
  if (test)
  {   ui->tableView_gp->setModel(Etmp.afficher());
      QMessageBox::information(nullptr,QObject::tr("ok"),
      QObject::tr("suppression effectué\n""Click cancel to exit."),
                               QMessageBox::Cancel);
  }
  else
      QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                            QObject::tr("suppression non effectué\n""Click cancel to exit."),
                                                     QMessageBox::Cancel);
}


void MainWindow_gp::on_pb_statistique_gp_clicked()
{
    // Créer un objet QChartView pour afficher le graphique


        // Obtenir les statistiques du Montant par type de design à partir de la base de données
        QMap<QString, double> prixMap;

        QSqlQuery query;
        query.prepare("SELECT gpnom, SUM(prix) FROM PRODUIT GROUP BY gpnom");

        if (query.exec()) {
            while (query.next()) {
                QString gpnom = query.value(0).toString();
                double gpprix = query.value(1).toDouble();
                prixMap[gpnom] = gpprix;  // Ajout des résultats à PrixMap
                qDebug() << "gpnom " << gpnom << ", gpprix " << gpprix;
            }
        }

        // Calculer le Montant total pour chaque Designe
        double prixTotal = 0.0;
        for (double gpprix: prixMap.values()) {
            prixTotal += gpprix;
        }

        // Afficher le montant total pour chaque Designe
        for (const QString &gpnom : prixMap.keys()) {
            qDebug() << "prix total " << gpnom << ": " << prixMap[gpnom];
        }

        // Créer une série de données pour le graphique circulaire
        QPieSeries *series = new QPieSeries();

        // Ajouter les tranches au graphique et calculer les pourcentages
        for (const QString &gpnom : prixMap.keys()) {
            QPieSlice *slice = series->append(gpnom, prixMap[gpnom]);

            // Calculer le pourcentage en fonction du Montant total
            if (prixTotal != 0.0) {
                slice->setLabel(QString("%1\n%2%").arg(gpnom).arg((prixMap[gpnom] /prixTotal) * 100, 0, 'f', 1));
            } else {
                // Gérer le cas où MontantTotal est égal à zéro (éviter la division par zéro)
                slice->setLabel(QString("%1\n0%").arg(gpnom));
            }
        }

        // Ajouter la série au graphique
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setTitle("satistique de produit ");
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
/*void MainWindow::updateProductInfo() {
    ui->productNameLabel->setText(E.getgpnom());
    ui->productPriceLabel->setText(QString::number(E.prix));  // Remove the parentheses
    ui->productQuantityLabel->setText(QString::number(E.nbr_produits));
}
void MainWindow::on_sellButton_clicked()
{
    // Validate input
    bool ok;
    int quantityToSell = ui->sellQuantityLineEdit->text().toInt(&ok);

    if (!ok || quantityToSell <= 0) {
        QMessageBox::warning(this, "Invalid Quantity", "Please enter a valid quantity to sell.");
        return;
    }

    // Perform the sale
    if (quantityToSell <= E.nbr_produits) {  // Remove the parentheses
        E.sell(quantityToSell);

        // Update the UI with the new quantity
        updateProductInfo();

        QMessageBox::information(this, "Sale Successful", "Product sold successfully!");
    } else {
        QMessageBox::warning(this, "Insufficient Quantity", "Not enough quantity in stock.");
    }
}*/
void MainWindow_gp::on_TRI_gp_clicked()
{
    QString sortParam = ui->trier_gp->currentText(); // Get the selected sort parameter

         QSqlQueryModel *sortedModel = new QSqlQueryModel();

         if (sortParam == "gpnom") {
             sortedModel->setQuery("SELECT * FROM PRODUIT ORDER BY gpnom ASC");
         } else if (sortParam == "prix") {
             sortedModel->setQuery("SELECT * FROM PRODUIT ORDER BY PRIX ASC");
         } else if (sortParam == "date") {
             sortedModel->setQuery("SELECT * FROM PRODUIT ORDER BY DATE_PRODUIT ASC");
         }

         ui->tableView_gp->setModel(sortedModel);
}
void MainWindow_gp::on_sellproduct_clicked()
{
    // Get the gpreference number and quantity from the UI
    int gpref = ui->refLineEdit->text().toInt();
    int quantity = ui->quantitySpinBox->value();

    // Create a QSqlQuery object to interact with the database
    QSqlQuery query;

    // Prepare an SQL query to get the current number of products
    query.prepare("SELECT nbr_produits FROM PRODUIT WHERE gpref = :gpref");
    query.bindValue(":gpref", gpref);

    // Execute the query
    if (query.exec() && query.next()) {
        // Get the current number of products
        int currentNumber = query.value(0).toInt();

        // Check if there are enough products to sell
        if (currentNumber >= quantity) {
            // Prepare an SQL query to update the number of products
            query.prepare("UPDATE PRODUIT SET nbr_produits = :nbr_produits WHERE gpref = :gpref");
            query.bindValue(":nbr_produits", currentNumber - quantity);
            query.bindValue(":gpref", gpref);

            // Execute the query
            if (!query.exec()) {
                // Handle the error
                qDebug() << "Failed to sell product: " << query.lastError();
            } else {
                // Display a success message
                QMessageBox::information(this, "Success", "Product sold successfully!");
            }
        } else {
            // Handle the error
            qDebug() << "Not enough products to sell";
            // Display an error message
            QMessageBox::warning(this, "Error", "Not enough products to sell");
        }
    } else {
        // Handle the error
        qDebug() << "Failed to get product: " << query.lastError();
        // Display an error message
        QMessageBox::warning(this, "Error", "Failed to get product");
    }
}
void MainWindow_gp::displayLogHistory()
{
    // Create a new model
    QStandardItemModel *model = new QStandardItemModel(this);

    // Open the log file for reading
    QFile logFile("actions.log");
    if (!logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening the log file for reading:" << logFile.errorString();
        delete model;  // Clean up the model in case of an error
        return;
    }

    // Create headers for the model
    model->setHorizontalHeaderLabels(QStringList() << "Timestamp" << "ActionType" << "ActionDetails");

    // Create a QTextStream to read from the file
    QTextStream in(&logFile);

    // Read and display each line from the file
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(' ');

        // Check if the line has enough parts (columns)
        if (parts.size() >= 3) {
            // Extract the date and time from the first two parts
            QDateTime dateTime = QDateTime::fromString(parts[0] + ' ' + parts[1], "yyyy-MM-dd hh:mm:ss");

            // ActionType is the third part
            QString actionType = parts[2] +" "+ parts[3];

            // ActionDetails is the concatenation of the remaining parts
            QString actionDetails = parts.mid(4).join(' ');

            // Add a new row to the model
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(dateTime.toString("yyyy-MM-dd hh:mm:ss")));
            rowItems.append(new QStandardItem(actionType));
            rowItems.append(new QStandardItem(actionDetails));
            model->insertRow(0, rowItems);  // Insert at the beginning of the model
        }
    }

    // Close the file
    logFile.close();

    // Set the model for the QTableView
    ui->historiquegp->setModel(model);

    // Additional settings (optional)
    ui->historiquegp->resizeColumnsToContents();  // Adjust column widths
    ui->historiquegp->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // Stretch the last column

    // Additional debug output
    qDebug() << "Number of rows in the table view:" << ui->historiquegp->model()->rowCount();
}

void MainWindow_gp::on_refreshhgp_clicked()
{
    displayLogHistory();
}
