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

// Retourne l'id de la rubrique
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
    return "";
}

// Retourne le budget de la rubrique
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
            return "";
    }
}

// Retourne le budget global alloué aux entités
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

// Retourne le Budget consommé par les entités
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

// Retourne le Budget restant des entités
QString Rubrique::getBudgetRest(){
    return QString::number(budgetGlob - budgetCons);
}

// Initalise le tableau des Entités relatives à une rubrique
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

// Retourne le nom d'une entité
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
    return "";
}

// Initialise un comboBox contenant toutes les rubriques
void Rubrique::initComboAll(QComboBox *combo){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text() + " Combo");
    }
    else {
        QSqlQuery query;
        QString q = "SELECT nom FROM rubrique";
            query.exec(q);

            while(query.next()) {
                combo->addItem(query.value(0).toString());
            }
    }
}

// Initialise un comboBox contenant toutes les entités
void Rubrique::initComboEntite(QComboBox *combo){
    combo->clear();
    combo->addItem("");
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text() + " Combo");
    }
    else {
        QSqlQuery query;
        QString q = "SELECT nom FROM entite";
            query.exec(q);

            while(query.next()) {
                combo->addItem(query.value(0).toString());
            }
    }
}

// Bouton ajouter une rubrique
void Rubrique::addRubrique(QString nom, QString budget)
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Add");
        return;
    }
    else {
        QSqlQuery query;
        QString q = "INSERT INTO rubrique VALUES('','"+nom+"','"+budget+"')";
            query.exec(q);
            return;
    }
}

// Bouton éditer une rubrique
void Rubrique::editRubrique(QString rubrique, QString nom, QString budget)
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Edit");
        return;
    }
    else {
        QSqlQuery query;
        QString q = "UPDATE rubrique SET nom='"+nom+"', budget='"+budget+"' WHERE nom LIKE '"+rubrique+"'";
            query.exec(q);
            return;
    }
}

// Bouton supprimer une rubrique
void Rubrique::deleteRubrique(QString nom)
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Delete");
        return;
    }
    else {
        QSqlQuery query;
        QString q = "DELETE FROM rubrique WHERE nom LIKE '"+nom+"'";
            query.exec(q);
            return;
    }
}

// Retourne si une rubrique existe ou pas
bool Rubrique::exists()
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Exist");
        return true;
    }
    else {
        QSqlQuery query;
        QString q = "SELECT id FROM rubrique WHERE nom LIKE '"+nom+"'";
            query.exec(q);
            while(query.next()) {
                return true;
            }
    }
    return false;
}

// Retourne le budget d'une rubrique d'une entité
QString Rubrique::getBudgetParEntite(QString entite, QPushButton *bouton, QGroupBox *group, QLabel *idBudget)
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text() + " Budget par Entité");
        return "";
    }
    else {
        QSqlQuery query;
        QString q = "SELECT budget,id FROM budget WHERE id_entite='"+getIdEntite(entite)+"' AND id_rubrique='"+id+"'";
            query.exec(q);
            while(query.next()) {
                idBudget->setText(query.value(1).toString());
                group->show();
                bouton->setText("Modifier Budget");
                return query.value(0).toString();
            }
    }
    idBudget->setText("");
    group->hide();
    bouton->setText("Ajouter Budget");
    return "";
}

// Retourne l'id d'une entité
QString Rubrique::getIdEntite(QString nom){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Id");
        return "";
    }
    else {
        QSqlQuery query;
        QString q = "SELECT id FROM entite WHERE nom LIKE '"+nom+"'";
            query.exec(q);
            while(query.next()) {
                return query.value(0).toString();
            }
    }
    return "";

}

// Ajoute le budget d'une rubrique d'une entité
void Rubrique::addBudgetEntite(QString nom, QString budget)
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Add Budget Entite");
        return;
    }
    else {
        QSqlQuery query;
        QString q = "INSERT INTO budget VALUES('','"+getIdEntite(nom)+"','"+id+"','"+budget+"','0')";
            query.exec(q);
            return;
    }
}

// Edite le budget d'une rubrique d'une entité
void Rubrique::editBudgetEntite(QString nom, QString budget)
{
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Edit Budget Entite");
        return;
    }
    else {
        QSqlQuery query;
        QString q = "UPDATE budget SET budget='"+budget+"' WHERE id_entite='"+getIdEntite(nom)+"' AND id_rubrique='"+id+"'";
            query.exec(q);
            return;
    }
}


