#include "gestionentite.h"

GestionEntite::GestionEntite(QString nom)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("alizetas");

    this->nom = nom;
    //this->id = getId();
    this->budgetGlob = 0;
    this->budgetCons = 0;
}
void GestionEntite::ajouterEntite(QLineEdit *nomEntite,QLineEdit *respEntite){
    QString name=nomEntite->text();
    QString nomResp=respEntite->text();

   if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Id");
        return ;
    }
    else {
       if(!name.isEmpty()){
        QSqlQuery query;

        QString q = "SELECT id FROM entite WHERE nom LIKE '"+name+"'";
            query.exec(q);
            while(query.next()){
                QMessageBox::critical(0, QObject::tr("Entite"),
                                      db.lastError().text()+  name + "exite dejas");
                return ;

            }

              //Requête pour ajouter une nouvelle entite

               QString insert="INSERT into entite (nom,responsable ) values( '"+name+"','"+nomResp+"')";

                      query.exec(insert);
                      QMessageBox::critical(0, "Ajout",
                                            name +" a été ajouter! ");
       }else{

           QMessageBox::critical(0, "Warmin",
                                 "Vous n'avez pas spécifier le nom a ajouté ! ");


       }



    }


}
void GestionEntite::modifierEntite(QLineEdit *nomEntite,QLineEdit *respEntite){
    QString name=nomEntite->text();
    QString nomResp=respEntite->text();

   if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Id");
        return ;
    }
    else {
        QSqlQuery query;
        QString qid = "SELECT id FROM entite WHERE nom LIKE '"+name+"'";
            query.exec(qid);
            QString idd=query.value(0).toString();
        QString q="UPDATE entite SET nom='"+name+"' , responsable='"+ nomResp+"' WHERE id LIKE '"+idd+"'";

          query.exec(q);
   }

 }
void GestionEntite::misjajourComboxRecherche(QComboBox * comboSearchEntite){

    if (!db.open()){
         QMessageBox::critical(0, QObject::tr("Database Error"),
                               db.lastError().text()+" Id");
         return ;
     }
     else {

         QSqlQuery query;
         QString qid = "Select nom FROM entite ";
             query.exec(qid);
             while(query.next()){
             comboSearchEntite->addItem(query.value(0).toString());

             }
    }

}


void GestionEntite::deleteEntite(QLineEdit *nomEntite){
    QString name=nomEntite->text();


    if (!db.open()){
         QMessageBox::critical(0, QObject::tr("Database Error"),
                               db.lastError().text()+" Id");
         return ;
     }
     else {
        if(!name.isEmpty()){
         QSqlQuery query;
         QString qid = "DELETE FROM entite WHERE nom LIKE '"+name+"'";
             query.exec(qid);
             QMessageBox::critical(0, "Test",
                                    name+ " a ete supprimer");}
        else{
            QMessageBox::critical(0, "Test",
                                  "Vous n'avez pas spécifier l'entite a supprimer");

        }

    }

 }
QString GestionEntite::getId(QString nom){
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
}

QString GestionEntite::getBudget(){
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
QString GestionEntite::getNomResponsable(QString nom){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text()+" Id");
        return "";
    }
    else {
        QSqlQuery query;
        QString q = "SELECT responsable FROM entite WHERE nom LIKE '"+nom+"'";
            query.exec(q);
            while(query.next()) {
                return query.value(0).toString();
            }
    }


}
QString GestionEntite::getBudgetGlob(QString nom){
    QSqlQuery query;
    QString id ;
    QString req = "SELECT id FROM entite WHERE nom LIKE '"+nom+"'";
        query.exec(req);
        while(query.next()) {
           id = query.value(0).toString();
        }


     QString    q = "SELECT  budget FROM budget WHERE id_entite='"+id+"'";

                    query.exec(q);

                    int budgetGlob=0;
                    while(query.next()) {
                        budgetGlob += query.value(0).toInt();
                    }
            return QString::number(budgetGlob);
}

QString GestionEntite::getBudgetCons(){
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

QString GestionEntite::getBudgetRest(){
    return QString::number(budgetGlob - budgetCons);
}

void GestionEntite::setTable(QTableWidget *table)
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

QString GestionEntite::getNomEntite(QString id)
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


