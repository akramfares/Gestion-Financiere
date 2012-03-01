#ifndef GESTIONENTITE_H
#define GESTIONENTITE_H
#include <QString>
#include <QSqlDatabase>
#include "admindialog.h"
#include "ui_admindialog.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>


class GestionEntite
{
public:
    GestionEntite(QString nom);
    GestionEntite();
    QString getId(QString nom);
    QString getNomResponsable(QString nom);
    QString getNom();
    QString getBudget();
    QString getBudgetGlob(QString nom);
    QString getBudgetCons();
    QString getBudgetRest();
    QString getNomEntite(QString id);
    void ajouterEntite(QLineEdit *nomEntite,QLineEdit *respEntite);
    void modifierEntite(QLineEdit *nomEntite,QLineEdit *respEntite);
    void deleteEntite(QLineEdit *nomEntite);
    void misjajourComboxRecherche(QComboBox * comboSearchEntite);




    void setTable(QTableWidget *table);
private:
    QSqlDatabase db;
    QString id;
    QString nom;
    int budgetGlob;
    int budgetCons;
};

#endif // GESTIONENTITE_H
