#ifndef CONSOMMATION_H
#define CONSOMMATION_H

#include <QString>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

class Consommation
{
public:
    Consommation(QString id);
    bool isValid(QString consomme);
    void addConsommation(QString consommation, QString fournisseur, QString commentaire);
private:
    QSqlDatabase db;
    QString id;
};

#endif // CONSOMMATION_H
