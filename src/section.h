#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QApplication>

class client
{
public:
    client(): GS_nom(""), GS_surface(""), GS_type(""), GS_mineralLevel(0.0), GS_temperature(0.0) {}
    client(QString GS_nom, QString GS_surface, QString GS_type, double GS_mineralLevel, double GS_temperature);

    void setGS_nom(QString n) { GS_nom = n; }
    void setGS_surface(QString n) { GS_surface = n; }
    void setGS_type(QString n) { GS_type = n; }

    // Setters and Getters for mineralLevel
    void GS_setMineralLevel(double level) { GS_mineralLevel = level; }
    double GS_getMineralLevel() const { return GS_mineralLevel; }

    // Setters and Getters for temperature
    void GS_setTemperature(double temp) { GS_temperature = temp; }
    double GS_getTemperature() const { return GS_temperature; }

    QString getGS_nom() { return GS_nom; }
    QString getGS_surface() { return GS_surface; }
    QString getGS_type() { return GS_type; }

    bool GS_ajouter();
    QSqlQueryModel *GS_afficher();
    bool GS_supprimer(QString);
    bool GS_modifier(QString);
    QSqlQueryModel *GS_trier(int test);
    QSqlQueryModel *GS_trierParAttribut(const QString &attribut, bool isNumeric);

    bool GS_chercher(const QString &valeur);
    bool GS_exportToPDF(const QString &filePath);
    QSqlQueryModel *GS_getAllData();
    QMap<QString, double> GS_calculateTypePercentage();
    QMap<QString, int> GS_calculateSurfaceStatistics();
    void GS_performOperations(double mineralLevel, double temperature);
    void GS_performOperations();
    QString GS_planCrop(const QString &material, double temperature);
    bool GS_printToPDF(QString filePath);

private:
    QString GS_nom;
    QString GS_surface;
    QString GS_type;
    double GS_mineralLevel;
    double GS_temperature;
};

#endif // SECTION_H
