#include "rubrique.h"

Rubrique::Rubrique(QString nom)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("");

    this->nom = nom;
    this->id = getId();
    this->budgetGlob = 0;
    this->budgetCons = 0;
}

QString Rubrique::getId(){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Id");
        return "";
    }
    else {
        QSqlQuery query;
        QString q = "SELECT id FROM rubrique WHERE nom LIKE '"+nom+"'";
            query.exec(q);
            while(query.next()) {
                return query.value(0).toString();
            }
    }
}

QString Rubrique::getBudget(){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
        return "";
    }
    else {
        QSqlQuery query;
        QString q = "SELECT budget FROM rubrique WHERE nom LIKE '"+nom+"'";
            query.exec(q);
            while(query.next()) {
                return query.value(0).toString();
            }
    }
}

QString Rubrique::getBudgetGlob(){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Glob");
        return "";
    }
    else {
        QSqlQuery query;
        QString q = "SELECT budget FROM budget WHERE id_rubrique ='"+id+"'";
            query.exec(q);
            while(query.next()) {
                budgetGlob += query.value(0).toInt();
            }
            return QString::number(budgetGlob);
    }

}

QString Rubrique::getBudgetCons(){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Cons");
        return "";
    }
    else {
        QSqlQuery query;
        QString q = "SELECT consomme FROM budget WHERE id_rubrique ='"+id+"'";
            query.exec(q);
            while(query.next()) {
                budgetCons += query.value(0).toInt();
            }
            return QString::number(budgetCons);
    }

}

QString Rubrique::getBudgetRest(){
    return QString::number(budgetGlob - budgetCons);
}

void Rubrique::setTable(QTableWidget *table)
{
    // Initialisations
    QString entite,budget,consomme,restant,q;
    QSqlQuery query;
    int count=0;

    // Vider le tableau
    for(int i=0;i<table->verticalHeader()->count();i++) table->removeRow(i);

    // Lecture seule
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    q = "SELECT  id_entite,budget,consomme FROM budget WHERE id_rubrique='"+id+"'";
    query.exec(q);
    while(count<query.size()) {
        query.next();

        entite = getNomEntite(query.value(0).toString());
        budget = query.value(1).toString();
        consomme = query.value(2).toString();
        restant = QString::number(query.value(1).toInt() - query.value(2).toInt());

        // Insertion dans Tableau
        // Entite
        table->insertRow(count);
        QTableWidgetItem *r = new QTableWidgetItem;
        r->setText(entite);
        table->setItem(count,0,r);

        // Budget Alloué
        QTableWidgetItem *bt = new QTableWidgetItem;
        bt->setText(budget);
        table->setItem(count,1,bt);

        // Busget Consommé
        QTableWidgetItem *bc = new QTableWidgetItem;
        bc->setText(consomme);
        table->setItem(count,2,bc);

        // Budget Restant
        QTableWidgetItem *br = new QTableWidgetItem;
        br->setText(restant);
        table->setItem(count,3,br);

        count++;
    }

}

QString Rubrique::getNomEntite(QString id)
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
        return "";
    }
    else {
        QSqlQuery query;
        QString q = "SELECT nom FROM entite WHERE id ='"+id+"'";
            query.exec(q);
            while(query.next()) {
                return query.value(0).toString();
            }
    }
}


