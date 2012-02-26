#include "consommation.h"

Consommation::Consommation(QString id)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("");

    this->id = id;
}

bool Consommation::isValid(QString consomme){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Conso Valid");
        return false;
    }
    else {
        QSqlQuery query;
        QString q = "SELECT budget - ( consomme + "+consomme+" ) FROM budget WHERE id ='"+id+"'";
            query.exec(q);
            while(query.next()) {
                if(query.value(0).toInt() >= 0) return true;
            }
    }
    return false;
}

void Consommation::addConsommation(QString consommation, QString fournisseur, QString commentaire)
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Add Conso");
        return;
    }
    else {
        QSqlQuery query;
        QString q = "INSERT INTO consommation VALUES('','"+id+"','"+consommation+"','"+fournisseur+"','"+commentaire+"',NOW())";
            query.exec(q);
            return;
    }
}
