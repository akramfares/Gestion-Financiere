#ifndef GENERAL_H
#define GENERAL_H

#include <QString>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QLineEdit>

class General
{
public:
    General();
    bool checkConnexion(QString login, QString password);
    void updateInfos(QLineEdit *etablissement, QLineEdit *bdgGlobal, QLineEdit *login);
    void setInfos(QString etablissement, QString bdgGlobal, QString login, QString password);
private:
    QSqlDatabase db;
};

#endif // GENERAL_H
