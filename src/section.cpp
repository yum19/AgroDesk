#include "section.h"
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlQuery>


client::client(QString GS_nom, QString GS_surface, QString GS_type, double GS_temperature, double GS_mineralLevel)
    : GS_nom(GS_nom), GS_surface(GS_surface), GS_type(GS_type), GS_temperature(GS_temperature), GS_mineralLevel(GS_mineralLevel) {}

bool client::GS_ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO section(nom_GS, surface_GS, type_GS, temperature_GS, mineralLevel_GS) VALUES(:nom_GS, :surface_GS, :type_GS, :temperature_GS, :mineralLevel_GS)");
    query.bindValue(":nom_GS", GS_nom);
    query.bindValue(":surface_GS", GS_surface);
    query.bindValue(":type_GS", GS_type);
    query.bindValue(":temperature_GS", GS_temperature);
    query.bindValue(":mineralLevel_GS", GS_mineralLevel);
    return query.exec();
}

bool client::GS_supprimer(QString nom_GS)
{
    QSqlQuery query;
    query.prepare("DELETE FROM section WHERE nom_GS = :nom_GS");
    query.bindValue(":nom_GS", nom_GS);
    return query.exec();
}

QSqlQueryModel *client::GS_afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM section");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_GS"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("surface_GS"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type_GS"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("temperature_GS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mineralLevel_GS"));

    return model;
}

bool client::GS_modifier(QString res)
{
    QSqlQuery query;

    query.prepare("UPDATE section SET surface_GS=:GS_surface, type_GS=:GS_type, temperature_GS=:GS_temperature, mineralLevel_GS=:GS_mineralLevel WHERE nom_GS=:gs_nom");
    query.bindValue(":gs_nom", res);
    query.bindValue(":GS_surface", GS_surface);
    query.bindValue(":GS_type", GS_type);
    query.bindValue(":GS_temperature", GS_temperature);
    query.bindValue(":GS_mineralLevel", GS_mineralLevel);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du dossier d'section:" << query.lastError().text();
        return false;
    }

    return true;
}



bool client::GS_chercher(const QString &valeur)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM section WHERE nom_GS = :value");
    query.bindValue(":value", valeur);

    if (query.exec()) {
        // Check if any records were found
        if (query.next()) {
            // Record found
            return true;
        } else {
            // Record not found
            return false;
        }
    } else {
        qDebug() << "Erreur lors de la recherche d'e section:" << query.lastError().text();
        return false;
    }
}

bool client::GS_exportToPDF(const QString &filePath)
{
    QSqlQueryModel *model = GS_afficher(); // Retrieve the data from the database

    if (!model)
    {
        qDebug() << "Failed to retrieve data from the database.";
        return false;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QPainter painter;
    painter.begin(&printer);

    // Create a table widget to hold the data
    QTableWidget table;
    table.setRowCount(model->rowCount());
    table.setColumnCount(model->columnCount());

    // Populate the table widget with data from the model
    for (int row = 0; row < model->rowCount(); ++row)
    {
        for (int col = 0; col < model->columnCount(); ++col)
        {
            QTableWidgetItem *item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            table.setItem(row, col, item);
        }
    }

    // Set up painter for PDF
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Define font and other styling options
    QFont font;
    font.setPointSize(12);
    painter.setFont(font);

    // Print the table to the PDF
    table.render(&painter);

    painter.end();

    return true;
}



QSqlQueryModel *client::GS_trierParAttribut(const QString &attribut, bool isNumeric)
{
    QSqlQueryModel *model = new QSqlQueryModel();

        if (isNumeric) {
            model->setQuery(QString("SELECT * FROM section ORDER BY %1 + 0").arg(attribut));
        } else {
            model->setQuery(QString("SELECT * FROM section ORDER BY %1").arg(attribut));
        }

        if (model->lastError().isValid()) {
            qDebug() << "Erreur lors du tri du dossier d'section:" << model->lastError().text();
            delete model;
            return nullptr;
        }

        return model;
}

QSqlQueryModel *client::GS_getAllData()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM section");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la récupération des données:" << model->lastError().text();
        delete model;
        return nullptr;
    }

    return model;
}
QMap<QString, double> client::GS_calculateTypePercentage()
{
    QSqlQuery query;
        query.prepare("SELECT GS_type, COUNT(*) as count FROM section GROUP BY GS_type");

        if (!query.exec()) {
            qDebug() << "Erreur lors du calcul des pourcentages par type:" << query.lastError().text();
            return QMap<QString, double>();
        }

        QMap<QString, double> typePercentages;
        int totalRecords = 0;

        while (query.next()) {
            QString type = query.value("type").toString();
            int count = query.value("count").toInt();
            totalRecords += count;
            typePercentages[type] = count;
        }

        if (totalRecords == 0) {
            qDebug() << "Aucun enregistrement trouvé.";
            return QMap<QString, double>();
        }

        // Calculate percentages
        for (auto it = typePercentages.begin(); it != typePercentages.end(); ++it) {
            it.value() = (it.value() / totalRecords) * 100.0;
        }

        return typePercentages;
}
QMap<QString, int> client::GS_calculateSurfaceStatistics()
{
    QSqlQuery query;
    query.prepare("SELECT surface_GS FROM section");

    if (!query.exec()) {
        qDebug() << "Erreur lors du calcul des statistiques de surface:" << query.lastError().text();
        return QMap<QString, int>();
    }

    QMap<QString, int> surfaceStatistics;
    int grandeSurfaceCount = 0;
    int petiteSurfaceCount = 0;
    int moyenneSurfaceCount = 0;

    while (query.next()) {
        int surfaceValue = query.value("surface").toInt();

        if (surfaceValue >= 1500 && surfaceValue <= 8000) {
            ++grandeSurfaceCount;
        } else if (surfaceValue >= 700 && surfaceValue < 1500) {
            ++moyenneSurfaceCount;
        } else if (surfaceValue >= 0 && surfaceValue < 700) {
            ++petiteSurfaceCount;
        }
    }

    surfaceStatistics["Grande Surface"] = grandeSurfaceCount;
    surfaceStatistics["Moyenne Surface"] = moyenneSurfaceCount;
    surfaceStatistics["Petite Surface"] = petiteSurfaceCount;

    return surfaceStatistics;
}
void client::GS_performOperations(double mineralLevel_GS, double temperature_GS)
{
    // Example: Print input parameters
    qDebug() << "Mineral Level: " << mineralLevel_GS;
    qDebug() << "Temperature: " << temperature_GS;

    // Add your own logic or calculations based on the input parameters here
    // For example, you can perform some conditional checks, calculations, etc.
}
QString client::GS_planCrop(const QString &material, double temperature)
{
    QString message;

    if (temperature >= 25.0) {
        message = "You can plan potatoes.";
    } else if (temperature >= 10.0) {
        message = "You can plan tomatoes.";
    } else {
        message = "The temperature is not suitable for planning any crops.";
    }

    return message;
}
