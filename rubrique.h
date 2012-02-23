#ifndef RUBRIQUE_H
#define RUBRIQUE_H

#include <QString>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QComboBox>

class Rubrique
{
public:
    Rubrique();
    Rubrique(QString nom);
    QString getId();
    QString getNom();
    QString getBudget();
    QString getBudgetGlob();
    QString getBudgetCons();
    QString getBudgetRest();
    QString getNomEntite(QString id);
    void setTable(QTableWidget *table);
    void initComboAll(QComboBox *combo);
    void initComboEntite(QComboBox *combo);
    void addRubrique(QString nom, QString budget);
    void editRubrique(QString rubrique,QString nom, QString budget);
    bool exists();

private:
    QSqlDatabase db;
    QString id;
    QString nom;
    int budgetGlob;
    int budgetCons;
};

#endif // RUBRIQUE_H
