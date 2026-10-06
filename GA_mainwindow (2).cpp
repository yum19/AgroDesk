#include "animaux.h"
#include"connection.h"
#include<QMessageBox>
#include<QApplication>
#include"GA_mainwindow.h"
#include <QComboBox>
#include <QIntValidator>
#include "ui_GA_mainwindow.h"
#include<QDateTime>
#include "reminder.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTextCursor>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include "login.h"
#include "menu.h"






MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int ret=GA_A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< GA_A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<GA_A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(GA_A.getserial(),SIGNAL(readyRead()),this,SLOT(on_GA_manualButton_clicked())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
    ui->GA_tableView1->setModel(GA_p.GA_afficher());
    ui->GA_le_id->setValidator(new QIntValidator(10000000,99999999,this));
    ui->GA_le_poids->setValidator(new QIntValidator(1000,99999999,this));
    QTimer* reminderTimer = new QTimer(this);
    connect(reminderTimer, &QTimer::timeout, this, &MainWindow::GA_checkReminders);
    reminderTimer->start(60000);
    connect(ui->GA_resetButton, &QPushButton::clicked, this, &MainWindow::on_GA_resetButton_clicked);
    connect(ui->GA_pdfButton, &QPushButton::clicked, this, &MainWindow::on_GA_exportToPDF_clicked);
    connect(ui->GA_stat, &QPushButton::clicked, this, &MainWindow::on_GA_stat_clicked);
    //QPushButton *quitter = new QPushButton("Quitter", this);
    connect(ui->GA_quitter, &QPushButton::clicked, this, &MainWindow::on_GA_quitter_clicked);








}


MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    int poids=ui->le_poids->text().toInt();
    QString type=ui->le_type->text();
    QString sexe=ui->le_sexe->text();
    QString date_enter=ui->le_date_enter->text();
    QString date_sortie=ui->le_date_sortie->text();
    QString dernier_vaccination=ui->le_dernier_vaccination->text();
    QString prochaine_vaccination=ui->le_prochaine_vaccination->text();
    QString malade=ui->le_malade->text();

    Animaux p(id,poids,type,sexe,date_enter,date_sortie,dernier_vaccination,prochaine_vaccination,malade);

    bool test=p.ajouter();
  if(test)
  {
  ui->tableView1->setModel(p.afficher());
  QMessageBox::information(nullptr,QObject::tr("succes"),
                QObject::tr("ajout effectué\n""Click cancel to exit."),QMessageBox::Cancel);

 }
  else
  {
      QMessageBox::critical(nullptr,QObject::tr("erreur"),
                  QObject::tr("ajout non effectué.\n"),QMessageBox::Cancel);
}


}*/


void MainWindow::on_GA_ajouter_clicked()
{
    int GA_id=ui->GA_le_id->text().toInt();
    int GA_poids=ui->GA_le_poids->text().toInt();
    QString GA_type=ui->GA_le_type->text();
    QString GA_sexe=ui->GA_le_sexe->text();
    QString GA_date_enter=ui->GA_le_date_enter->text();
    QString GA_date_sortie=ui->GA_le_date_sortie->text();
    QString GA_dernier_vaccination=ui->GA_le_dernier_vaccination->text();
    QString GA_prochaine_vaccination=ui->GA_le_prochaine_vaccination->text();
    QString GA_malade=ui->GA_le_malade->text();

    Animaux GA_p(GA_id, GA_poids, GA_type, GA_sexe, GA_date_enter, GA_date_sortie, GA_dernier_vaccination, GA_prochaine_vaccination, GA_malade);

    bool test = GA_p.GA_ajouter();

    if (test)
    {
        ui->GA_tableView1->setModel(GA_p.GA_afficher());
        QMessageBox::information(this, "Succès", "Ajout effectué. Cliquez sur Cancel  pour quitter.", QMessageBox::Cancel);

        // Perform data retrieval for tableView2
        GA_updateTableView2();

    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Ajout non effectué.", QMessageBox::Cancel);
    }
}

void MainWindow::GA_updateTableView1()
{
    int GA_id=ui->GA_le_id->text().toInt();
    QString GA_type=ui->GA_le_type->text();
    QString GA_dernier_vaccination=ui->GA_le_dernier_vaccination->text();
    QString GA_prochaine_vaccination=ui->GA_le_prochaine_vaccination->text();
    QString GA_malade=ui->GA_le_malade->text();
    if (GA_malade == "oui")
    {
        // Fetch 'id', 'prochaine_vaccination', and 'dernier_vaccination' columns for malade animals
        QSqlQuery query;
        query.exec("SELECT GA_id,GA_type, GA_prochaine_vaccination, GA_dernier_vaccination FROM animau WHERE GA_malade = 'oui'"); // Replace with your table name

        QSqlQueryModel* model2 = new QSqlQueryModel();
        model2->setQuery(query);

        // Set model2 for tableView2
        ui->GA_tableView1->setModel(model2);

        // Insert the data into the "alert" table
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO animau (GA_id,GA_type, GA_prochaine_vaccination, GA_dernier_vaccination) VALUES (:GA_id, :GA_type, :GA_prochaine_vaccination, :GA_dernier_vaccination)");
        insertQuery.bindValue(":GA_id", GA_id); // Replace with the actual values
        insertQuery.bindValue(":GA_type",GA_type);
        insertQuery.bindValue(":GA_prochaine_vaccination", GA_prochaine_vaccination);
        insertQuery.bindValue(":GA_dernier_vaccination", GA_dernier_vaccination);

        if (insertQuery.exec())
        {
            // Data inserted into "alert" table
        }
        else
        {
            qDebug() << "Erreur lors de l'insertion des données dans la table : " << insertQuery.lastError().text();
        }
    }
    else
    {
        ui->GA_tableView2->clearSpans(); // Clear tableView2 if 'malade' is not 'oui'
    }
}

void MainWindow::GA_updateTableView2()
{
    int GA_id=ui->GA_le_id->text().toInt();
    QString GA_type=ui->GA_le_type->text();
    QString GA_dernier_vaccination=ui->GA_le_dernier_vaccination->text();
    QString GA_prochaine_vaccination=ui->GA_le_prochaine_vaccination->text();
    QString GA_malade=ui->GA_le_malade->text();
    if (GA_malade == "oui")
    {
        // Fetch 'id', 'prochaine_vaccination', and 'dernier_vaccination' columns for malade animals
        QSqlQuery query;
        query.exec("SELECT GA_id,GA_type, GA_prochaine_vaccination, GA_dernier_vaccination FROM animau WHERE GA_malade = 'oui'"); // Replace with your table name

        QSqlQueryModel* model2 = new QSqlQueryModel();
        model2->setQuery(query);

        // Set model2 for tableView2
        ui->GA_tableView2->setModel(model2);

        // Insert the data into the "alert" table
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO alert (GA_id,type, GA_prochaine_vaccination, GA_dernier_vaccination) VALUES (:GA_id, :GA_type, :GA_prochaine_vaccination, :GA_dernier_vaccination)");
        insertQuery.bindValue(":GA_id", GA_id); // Replace with the actual values
        insertQuery.bindValue(":GA_type",GA_type);
        insertQuery.bindValue(":GA_prochaine_vaccination", GA_prochaine_vaccination);
        insertQuery.bindValue(":GA_dernier_vaccination", GA_dernier_vaccination);

        if (insertQuery.exec())
        {
            // Data inserted into "alert" table
        }
        else
        {
            qDebug() << "Erreur lors de l'insertion des données dans la table: " << insertQuery.lastError().text();
        }
    }
    else
    {
        ui->GA_tableView2->clearSpans(); // Clear tableView2 if 'malade' is not 'oui'
    }
}




void MainWindow::on_GA_modifier_clicked()
{
     int GA_id=ui->GA_le_id->text().toInt();
     int GA_poids=ui->GA_le_poids->text().toInt();
     QString GA_type=ui->GA_le_type->text();
     QString GA_sexe=ui->GA_le_sexe->text();
     QString GA_date_enter=ui->GA_le_date_enter->text();
     QString GA_date_sortie=ui->GA_le_date_sortie->text();
     QString GA_dernier_vaccination=ui->GA_le_dernier_vaccination->text();
     QString GA_prochaine_vaccination=ui->GA_le_prochaine_vaccination->text();
     QString GA_malade=ui->GA_le_malade->text();

  Animaux GA_Etmp(GA_id,GA_poids,GA_type,GA_sexe,GA_date_enter,GA_date_sortie,GA_dernier_vaccination,GA_prochaine_vaccination,GA_malade);
  bool test=GA_Etmp.GA_modifier(GA_id);


  if(test)
  {
    ui->GA_tableView1->setModel(GA_Etmp.GA_afficher());
  QMessageBox::information(nullptr,QObject::tr("ok"),
         QObject::tr("modification effectué\n""Cliquez sur Cancel pour quitter."),QMessageBox::Cancel);

 }
  else
  {
      QMessageBox::critical(nullptr,QObject::tr("not OK"),
          QObject::tr("modification non effectué.\n""Cliquez sur Cancel pour quitter."),QMessageBox::Cancel);
}
}


void MainWindow::on_GA_supprimer_clicked()
{
  Animaux GA_p1;
  GA_p1.setGA_id(ui->GA_le_supprimer->text().toInt());
  bool test=GA_p1.GA_supprimer(GA_p1.getGA_id());
   ui->GA_tableView1->setModel(GA_p1.GA_afficher());
  if(test)
  {
 ui->GA_tableView1->setModel(GA_p1.GA_afficher());
  QMessageBox::information(nullptr,QObject::tr("ok"),
            QObject::tr("suppression effectué\n""Cliquez sur Cancel pour quitter."),QMessageBox::Cancel);
  ui->GA_tableView1->setModel(GA_p1.GA_afficher());
 }
  else
  {
      QMessageBox::critical(nullptr,QObject::tr("not OK"),
             QObject::tr("suppression non effectué.\n""Cliquez sur Cancel pour quitter."),QMessageBox::Cancel);
}
}



void MainWindow::on_GA_analyzeButton_clicked()
{
    // Implement the analyze function to identify close vaccinations
    Animaux animal;
    QList<Animaux> closeVaccinations = animal.GA_getAnimals();

    QString alertMessage = "les alertes de vaccination les plus proches:\n";

    for (const Animaux& animal : closeVaccinations)
    {
        QDateTime vaccinationDate = QDateTime::fromString(animal.GA_getprochaine_vaccination(), "yyyy-MM-dd");
        int daysRemaining = QDate::currentDate().daysTo(vaccinationDate.date());

        if (daysRemaining <= 360)
        {
            alertMessage += QString("Animal ID: %1, type: %2, Jours restant: %3\n")
                .arg(animal.getGA_id()).arg(animal.getGA_type()).arg(daysRemaining);
        }
    }

    if (!closeVaccinations.isEmpty())
    {
        QMessageBox::information(this, "les alertes de vaccination les plus proches", alertMessage);
    }
    else
    {
        QMessageBox::information(this, "les alertes de vaccination les plus proches", "Aucune vaccination proche trouvée.");
    }
}

void MainWindow::on_GA_addReminderButton_clicked() {
    QString reminderText = ui->GA_reminderTextEdit->text();
    QDateTime reminderDateTime = ui->GA_reminderDateTimeEdit->dateTime();
    QString errorMessage;

    // Get the ID from the user
    int GA_id = ui->GA_le_id->text().toInt();

    // Check if the animal with the provided ID exists in the database
    if (Animal.GA_checkIfAnimalExists(GA_id) && Animal.GA_isAnimalSick(GA_id, errorMessage)) {
        // Add the reminder to the Reminder class
        reminder.addReminder(reminderText, reminderDateTime);


        // Show a confirmation message
        QMessageBox::information(this, "Alarm ajouté", "Alarm ajouté avec succès !");
    } else {
        QMessageBox::warning(this, "ID d'animal ou état de santé invalide", "L'identification de l'animal fournie n'existe pas ou l'animal est en bonne santé.");
    }


   }


void MainWindow::on_GA_showRemindersButton_clicked() {
    // Get the list of upcoming reminders from the Reminder class
    QList<ReminderInfo> upcomingReminders = reminder.getUpcomingReminders();

    // Display the reminders to the user
    if (!upcomingReminders.isEmpty()) {
        QString reminderList;
        for (const ReminderInfo& info : upcomingReminders) {
            reminderList += info.text + " at " + info.dateTime.toString() + "\n";
        }
        QMessageBox::information(this, "Rappels à venir", reminderList);
    } else {
        QMessageBox::information(this, "Rappels à venir", "Aucun rappel à venir trouvé.");
    }
}

void MainWindow::GA_checkReminders() {
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Check for upcoming reminders
    QList<ReminderInfo> upcomingReminders = reminder.getUpcomingReminders();

    for (const ReminderInfo& info : upcomingReminders) {
        if (info.dateTime <= currentDateTime.addSecs(60)) {  // Check if the reminder is within the next minute
            // Trigger the alert for this reminder
            // You can show a QMessageBox or implement your own notification mechanism
            QMessageBox::information(this, "Rappels à venir", info.text);
        }
    }
}

void MainWindow::on_GA_calculateProbabilityButton_clicked() {
    // Pass the selected symptoms from comboboxes and get the result
    QString result = animaux.GA_calculateIllness(ui->GA_comboBox1, ui->GA_comboBox2, ui->GA_comboBox3);

    // Display the result in a QLineEdit with red color
    ui->GA_resultLineEdit->setText(result);
    ui->GA_resultLineEdit->setStyleSheet("QLineEdit { color: brown; font-weight: bold; }");
}



void MainWindow::on_GA_rechercherButton_clicked() {
    QString GA_searchParam = ui->GA_comboBoxSearch->currentText(); // Get the selected search parameter
    QString GA_searchText = ui->GA_lineEditSearch->text(); // Get the text to search

    QSqlQueryModel *searchResultModel = new QSqlQueryModel();

    if (GA_searchParam == "type") {
        searchResultModel->setQuery(QString("SELECT * FROM ANIMAU WHERE GA_type = '%1'").arg(GA_searchText));
    } else if (GA_searchParam == "id") {
        bool isNumeric;
        int searchID = GA_searchText.toInt(&isNumeric);

        if (isNumeric) {
            searchResultModel->setQuery(QString("SELECT * FROM ANIMAU WHERE GA_id = %1").arg(searchID));
        } else {
            // Handle non-numeric input for ID (optional)
            // Show an error message or take appropriate action
        }
    } else if (GA_searchParam == "poids") {
        bool isNumeric;
        int searchPoids = GA_searchText.toInt(&isNumeric);

        if (isNumeric) {
            searchResultModel->setQuery(QString("SELECT * FROM ANIMAU WHERE GA_poids = %1").arg(searchPoids));
        } else {
            // Handle non-numeric input for poids (optional)
            // Show an error message or take appropriate action
        }
    }

    ui->GA_tableView1->setModel(searchResultModel);
}

void MainWindow::on_GA_trierButton_clicked() {
    QString GA_sortParam = ui->GA_comboBoxSort->currentText(); // Get the selected sort parameter

    QSqlQueryModel *sortedModel = new QSqlQueryModel();

    if (GA_sortParam == "type") {
        sortedModel->setQuery("SELECT * FROM ANIMAU ORDER BY GA_type ASC");
    } else if (GA_sortParam == "id") {
        sortedModel->setQuery("SELECT * FROM ANIMAU ORDER BY GA_id ASC");
    } else if (GA_sortParam == "poids") {
        sortedModel->setQuery("SELECT * FROM ANIMAU ORDER BY GA_poids ASC");
    }

    ui->GA_tableView1->setModel(sortedModel);
}

void MainWindow::on_GA_resetButton_clicked() {
    Animaux GA_p; // Assuming 'p' is an instance of your Animaux class

    // Revert to the original state by fetching the initial data
    ui->GA_tableView1->setModel(GA_p.GA_afficher());
}

void MainWindow::on_GA_exportToPDF_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
        if (filePath.isEmpty()) {
            return;
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);

        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing, true);

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM ANIMAU"); // Replace with your table name

        int rowCount = model->rowCount();
        int columnCount = model->columnCount();

        QTextDocument doc;
        QTextCursor cursor(&doc);

        QString htmlTable = "<table border='1' width='100%'>"; // Set the table width to 100%

        // Construct the table header
        htmlTable += "<tr>";
        for (int col = 0; col < columnCount; ++col) {
            htmlTable += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
        }
        htmlTable += "</tr>";

        // Populate the table with data
        for (int row = 0; row < rowCount; ++row) {
            htmlTable += "<tr>";
            for (int col = 0; col < columnCount; ++col) {
                htmlTable += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
            }
            htmlTable += "</tr>";
        }

        htmlTable += "</table>";

        doc.setHtml(htmlTable);
        doc.drawContents(&painter);

        painter.end();

        QMessageBox::information(this, "PDF Export", "PDF exported to " + filePath);
    }

void MainWindow::GA_showStatistics(QWidget *parent, QChartView *GA_chartView) {
    QSqlQuery query("SELECT GA_malade, COUNT(*) FROM ANIMAU GROUP BY GA_malade");
    QMap<QString, int> GA_data;
    while (query.next()) {
        QString GA_malade = query.value(0).toString();
        int count = query.value(1).toInt();
        GA_data[GA_malade] = count;
    }

    // Create a pie series with the data
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for (auto it = GA_data.begin(); it != GA_data.end(); ++it) {
        series->append(it.key(), it.value());
    }

    // Create a chart and add the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("malade vs non malade: Animaux");

    // Set the chart as the central widget of the chart view
    GA_chartView->setChart(chart);

    GA_chartView->setRenderHint(QPainter::Antialiasing);
    GA_chartView->setFixedSize(350, 300); // Set a fixed size (adjust as needed)

    QVBoxLayout *layout = new QVBoxLayout(parent);
    layout->addWidget(GA_chartView);
}

void MainWindow::on_GA_stat_clicked() {
    QChartView *GA_chartView = new QChartView();

    // Show the statistics in the existing widget
    GA_showStatistics(ui->GA_widget, GA_chartView);

    // Set the chart view as the central widget of the existing widget
    QVBoxLayout *layout = new QVBoxLayout(ui->GA_widget);
    layout->addWidget(GA_chartView);
}

void MainWindow::on_GA_quitter_clicked() {
    QApplication::quit(); // Close the application
}




void MainWindow::on_GA_manualButton_clicked() {
    // Assuming GA_A is an instance of your class handling Arduino communication
  data=GA_A.read_from_arduino();
  int GA_data=data.toInt();

  if(GA_data==1){

    GA_A.write_to_arduino("INC");

    int GA_id1 = ui->GA_animalIDLineEdit->text().toInt();
    int GA_desir = ui->GA_feedingGoalSpinBox->text().toInt();

    QSqlQuery query;
    query.prepare("SELECT inc, GA_desir FROM feed WHERE GA_id1 = :GA_id1");
    query.bindValue(":GA_id1", GA_id1);
    query.exec();

    if (query.next()) {
        int inc = query.value(0).toInt();
        //int storedDesir = query.value(1).toInt();

        query.prepare("UPDATE feed SET inc = :inc +1, GA_desir = :GA_desir WHERE GA_id1 = :GA_id1");
        query.bindValue(":inc", inc);
        query.bindValue(":GA_desir", GA_desir); // Update 'desir' in the database
        query.bindValue(":GA_id1", GA_id1);
        bool updateSuccess = query.exec();

        if (updateSuccess) {
            // Adjust delay based on updated 'desir' value
            int delayTime = GA_desir * 1000; // Convert desir to milliseconds

            char S[10];  // Buffer to hold the formatted delay time
            sprintf(S, "%d", delayTime);  // Format delayTime into a string
            GA_A.write_to_arduino(S);

            QMessageBox::information(this, "Succès", "Mise à jour effectuée. Cliquez sur Cancel pour quitter.", QMessageBox::Cancel);
            GA_updateTableView2();
        } else {
            QMessageBox::critical(this, "Erreur", "Mise à jour non effectuée.", QMessageBox::Cancel);
        }
    } else {
        query.prepare("INSERT INTO feed (GA_id1, GA_desir, inc) VALUES (:GA_id1, :GA_desir, 1)");
        query.bindValue(":GA_id1", GA_id1);
       query.bindValue(":GA_desir", GA_desir, QSql::In | QSql::Binary);
        bool insertSuccess = query.exec();

        if (insertSuccess) {
            int delayTime = GA_desir * 1000; // Convert desir to milliseconds

            char S[10];  // Buffer to hold the formatted delay time
            sprintf(S, "%d", delayTime);  // Format delayTime into a string

            GA_A.write_to_arduino(S);

            QMessageBox::information(this, "Succès", "Ajout effectué. Cliquez sur Cancel pour quitter.", QMessageBox::Cancel);
            GA_updateTableView2();
        } else {
            QMessageBox::critical(this, "Erreur", "Ajout non effectué.", QMessageBox::Cancel);
        }
    }
}
}

