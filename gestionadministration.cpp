#include "gestionadministration.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "mainwindow.h"

GestionAdministration::GestionAdministration(QWidget *parent):MainWindow(parent)
{
}
/*
  **************************************************************************************************
  **************************************************************************************************
  **Cette Methode permet de génerer une nouvelle page                                             **
  **Elle apour objectif de faire appel a la page                                                  **
  **Gestion qui permert d'administrer la gestion budgétaire                                       **
  **                                                                                              **
  **************************************************************************************************
 *****************************************************************************************************
*/
void GestionAdministration::on_bouton_connecter_currentIndexChanged(const QString &arg1)
{
    QMessageBox::information(0, QObject::tr("Ouverture de la page Gestion"),arg1);
    ui->BarreOutils->insertTab(3,ui->tabGestion,"Gestion");

    ui->BarreOutils->setCurrentIndex(3);
    setTableGestion(arg1);

}
/*********************************************************************************************************
  ********************************************************************************************************
  ** Cette methode methode joue un role capital dGestion de la base de donnée                           **
  ** Nous excutons des requete permet la mis a jour de la base                                          **
  **   Requête pour l'insertion dans le cas de de la table entite                                       **
  **                                                                                                    **
  ** Reque:                                                                                         **
  ** Nous excutons des requete permet la mis a jour de la base                                         **
  **   Requête pour l'insertion dans le cas de de la table entite                                       **
  **                                                                                                    **
  **                                                                                                    **
  ********************************************************************************************************
**********************************************************************************************************
*/
QString GestionAdministration::requete_insertion_entite( QString name,QString nameOfresp){
    QString reqInsertion = "INSERT INTO `entite` VALUES ('', 'name', 'nameOfresp')";

  return reqInsertion;
}
QString GestionAdministration::requete_suppression_entite(QString name){
    QString reqsurpression= "DELETE FROM `entite` where nomEntite=name";
    return reqsurpression ;

}
QString GestionAdministration::requete_mis_a_jour_entite(QString id,QString name , QString nameofresp){
    QSTring resmisjajour="UPDATE `entite` SET nom='name','nomREsponsable=nameofresp'' WHERE id=id";
    return  resmisjajour;
}



/*********************************************************************************************************
  ********************************************************************************************************
  ** Cette methode methode joue un role capital dGestion de la base de donnée                           **
  ** Nous excutons des requete permet la mis a jour de la base                                          **
  **   Requête pour l'insertion dans le cas de de la table entite                                       **
  **                                                                                                    **
  ** Reque:                                                                                         **
  ** Nous excutons des requete permet la mis a jour de la base                                          **
  **   Requête pour l'insertion dans le cas de de la table entite                                       **
  **                                                                                                    **
  **                                                                                                    **
  ********************************************************************************************************
**********************************************************************************************************
*/
QString GestionAdministration::requete_insertion_rubrique(QString nameofBudget,QString budgetofrubrique){
  QString requeteinsertion = "INSERT INTO `entite`  VALUES ('', 'nameofBudget', 'budgetorfurbrique')";
   return
}
QString GestionAdministration::requete_suppression_rubrique(){


}
QString GestionAdministration::requete_mis_a_jour_rubrique(){


}
/*********************************************************************************************************
  ********************************************************************************************************
  ** Cette methode methode joue un role capital dGestion de la base de donnée                           **
  ** Nous excutons des requete permet la mis a jour de la base                                          **
  **   Requête pour l'insertion dans le cas de de la table entite                                       **
  **                                                                                                    **
  ** Reque:                                                                                         **
  ** Nous excutons des requete permet la mis a jour de la base                                          **
  **   Requête pour l'insertion dans le cas de de la table entite                                       **
  **                                                                                                    **
  **                                                                                                    **
  ********************************************************************************************************
**********************************************************************************************************
*/
QString GestionAdministration::requete_affichage_info_enite(){


}
QString GestionAdministration::requete_affichage_info_rubrique(){


}


/*********************************************************************************************************
  ********************************************************************************************************
  ** Cette methode methode joue un role capital dGestion de la base de donnée                           **
  ** Nous excutons des requete permet la mis a jour de la base                                          **
  **   Requête pour l'insertion dans le cas de de la table entite                                       **
  **                                                                                                    **
  ** Reque:                                                                                         **
  ** Nous excutons des requete permet la mis a jour de la base                                          **
  **   Requête pour l'insertion dans le cas de de la table entite                                       **
  **                                                                                                    **
  **                                                                                                    **
  ********************************************************************************************************
**********************************************************************************************************
*/
void GestionAdministration::setTableGestion(QString nom){

    ui->tableEntite->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

            db.setHostName("localhost");
            db.setDatabaseName("gestionfinanciere");
            db.setUserName("root");
            db.setPassword("alizetas");
            if (!db.open()){
                QMessageBox::critical(0, QObject::tr("Database Error"),
                                      db.lastError().text());
            }
            else {
                QSqlQuery query,quer;
               QString nomEntite,nomResponsable;
               nomEntite=textNomEntite.getText();
               nomResponsable=textNomResponsable.getText();


                QString reqInsertion = "INSERT INTO `entite` (`id`, `nom`, `responsable`) VALUES (1, 'nomEntite', 'nomResponsable')";




                query.exec(reqInsertion);
                    QString id;

                    while(query.next()) {
                        id = query.value(0).toString();
                        nomEntite=query.value(1).toString();
                        nomResponsable=query.value(2).toString();
                        ui->nomEntiteLab->setText(nomEntite);
                        ui->nomRespLab->setText(nomResponsable);
                    }

                q = "SELECT  id_rubrique,budget,consomme FROM budget WHERE id_entite='";

                q.append(id);
                q.append("'");
                    query.exec(q);
                    int count=0;
                    QString nom,rubrique, budget, consomme,restant,budgetTotal,budgetTotalConso,budgeTotalRestant;
                    while(count<query.size()) {
                        query.next();
                        rubrique = query.value(0).toString();
                        budget = query.value(1).toString();
                        consomme = query.value(2).toString();


                            //Pour avoir le reste on fait juste total moins consommé
                        restant = QString::number( query.value(1).toInt()- query.value(2).toInt());


                     QString req= "SELECT nom FROM rubrique WHERE id='";

                     req.append(rubrique);
                     req.append("'");
                         quer.exec(req);quer.next();
                         nom= quer.value(0).toString();



                        ui->tableEntite->insertRow(count);
                        QTableWidgetItem *r = new QTableWidgetItem;
                        r->setText(nom);
                        ui->tableEntite->setItem(count,0,r);
                        QTableWidgetItem *bt = new QTableWidgetItem;
                        bt->setText(budget);
                        ui->tableEntite->setItem(count,1,bt);
                        QTableWidgetItem *bc = new QTableWidgetItem;
                        bc->setText(consomme);
                        ui->tableEntite->setItem(count,2,bc);
                        QTableWidgetItem *br = new QTableWidgetItem;
                        br->setText(restant);
                        ui->tableEntite->setItem(count,3,br);
                        count++;
                    }


            }
