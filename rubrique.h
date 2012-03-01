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
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

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
    QString getBudgetParEntite(QString entite, QPushButton *bouton, QGroupBox *group, QLabel *idBudget);
    QString getIdEntite(QString nom);
    void setTable(QTableWidget *table);
    void initComboAll(QComboBox *combo);
    void initComboEntite(QComboBox *combo);
    void addRubrique(QString nom, QString budget);
    void editRubrique(QString rubrique,QString nom, QString budget);
    void deleteRubrique(QString nom);
    void addBudgetEntite(QString nom, QString budget);
    void editBudgetEntite(QString nom, QString budget);
    bool exists();
private:
    QSqlDatabase db;
    QString id;
    QString nom;
    int budgetGlob;
    int budgetCons;
};

#endif // RUBRIQUE_H
