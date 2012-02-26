#include "general.h"

General::General()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("");
}

bool General::checkConnexion(QString login, QString password){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Check Connexion");
        return false;
    }
    else {
        QSqlQuery query;
        QString q = "SELECT id FROM general WHERE login ='"+login+"' AND password = '"+password+"'";
            query.exec(q);
            while(query.next()) {
               return true;
            }
    }
    return false;
}

void General::updateInfos(QLineEdit *etablissement, QLineEdit *bdgGlobal, QLineEdit *login){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Check Connexion");
        return;
    }
    else {
        QSqlQuery query;
        QString q = "SELECT etablissement,budgetGlobal,login FROM general LIMIT 1";
            query.exec(q);
            while(query.next()) {
                etablissement->setText(query.value(0).toString());
                bdgGlobal->setText(query.value(1).toString());
                login->setText(query.value(2).toString());
            }
    }
}

void General::setInfos(QString etablissement, QString bdgGlobal, QString login, QString password){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Edit");
        return;
    }
    else {
        QSqlQuery query;
        QString q = "UPDATE general SET etablissement='"+etablissement+"', budgetGlobal='"+bdgGlobal+"', login='"+login+"', password='"+password+"' LIMIT 1";
            query.exec(q);
            return;
    }

}
