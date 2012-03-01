#include "mainwindow.h"
#include <sstream>
#include "ui_mainwindow.h"
#include "rubrique.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include<QFontDialog>
#include<QColorDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QPrinter>
#include <QPrintDialog>
#include"gestionentite.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Suppression des onglets : Entité & Rubrique
    ui->BarreOutils->removeTab(1);
    ui->BarreOutils->removeTab(1);

    GestionEntite *ges = new GestionEntite("");

    //Mis ajour automatique de la liste deroulante des entités
    ges->misjajourComboxRecherche(ui->comboBox_3);
   misjajourComboxRubrique();
  // misjajourResponsable();

gestionMenu();

   // Initialisation des combos
    initCombos();
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(ouvrirDialogue()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCombos(){
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
    }
    else {
        QSqlQuery query;
        QString q = "SELECT nom FROM rubrique";
            query.exec(q);

            while(query.next()) {
                ui->comboRubrique->addItem(query.value(0).toString());
            }
    }
}

void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    // Connexion à la base de données
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("alizetas");

    ui->BarreOutils->insertTab(1,ui->tabEntite,"Entité");
    ui->BarreOutils->setCurrentIndex(1);
    setTableEntite(arg1);
}

void MainWindow::setTableEntite(QString nom){
    // Vider le tableau
    for(int i=0;i<ui->tableEntite->verticalHeader()->count();i++) ui->tableEntite->removeRow(i);

    ui->tableEntite->setEditTriggers(QAbstractItemView::NoEditTriggers);
            if (!db.open()){
                QMessageBox::critical(0, QObject::tr("Database Error"),
                                      db.lastError().text());
            }
            else {
                QSqlQuery query,quer;
                QString q = "SELECT * FROM entite WHERE nom LIKE '";
                QString nomEntite,nomResponsable;
                q.append(nom);
                q.append("'");
                    query.exec(q);
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
                    QString nom,rubrique, budget, consomme,restant;
                    int budgetGlob=0,budgetCons=0,budgetRest=0;
                    while(count<query.size()) {
                        query.next();
                        rubrique = query.value(0).toString();
                        budget = query.value(1).toString();
                        consomme = query.value(2).toString();
                        restant = QString::number( query.value(1).toInt()- query.value(2).toInt());

                        budgetGlob += query.value(1).toInt();
                        budgetCons += query.value(2).toInt();
                        budgetRest += query.value(1).toInt()- query.value(2).toInt();


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

                    ui->bdgGlobEntite->setText(QString::number(budgetGlob));
                    ui->bdgConsEntite->setText(QString::number(budgetCons));
                    ui->bdgRestEntite->setText(QString::number(budgetRest));


            }
}

void MainWindow::on_comboRubrique_currentIndexChanged(const QString &arg1)
{
    ui->BarreOutils->insertTab(1,ui->tabRubrique,"Rubrique");
    ui->BarreOutils->setCurrentIndex(1);
    setTableRubrique(arg1);
}

void MainWindow::setTableRubrique(QString nom){
    Rubrique *rubrique = new Rubrique(nom);

    // Nom Rubrique
    ui->nomRubrique->setText(nom);
    //Budget Rubrique
    ui->budgetRubrique->setText(rubrique->getBudget());
    // Budget alloué
    ui->bdgGlobRubrique->setText(rubrique->getBudgetGlob());
    // Budget consommé
    ui->bdgConsRubrique->setText(rubrique->getBudgetCons());
    // Budget Restant
    ui->bdgRestRubrique->setText(rubrique->getBudgetRest());
    // Tableau des Entités en relation avec la Rubrique
    rubrique->setTable(ui->tableRubrique);

}
void MainWindow::misjajourComboxRubrique(){
    // Connexion à la base de données
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("alizetas");
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
    }
     else {

         QSqlQuery query;
         QString qid = "SELECT nom FROM rubrique ";
             query.exec(qid);
             while(query.next()){
            ui->comboRubrique->addItem(query.value(0).toString());

             }
    }

}


void MainWindow::on_adminConnect_clicked()
{
        General *general = new General();

    if(general->checkConnexion(ui->lineEdit_10->text(),ui->lineEdit_9->text())){
        AdminDialog ad;

        ad.exec();
        ui->lineEdit_10->setText("");
        ui->lineEdit_9->setText("");
    }
    else {
        QMessageBox::critical(0, QObject::tr("Général"),
                              "Mauvais mot de passe !");

}


}
void MainWindow::aPropos(){


     QMessageBox::information(this, "Apropos",
     "L'Application Gestion Financière \n  a été realiser par\n  Akram Fares  \n Cheick Ismael MAIGA  ");

}
void MainWindow::gestionMenu(){

        ui->actionQuitter_3->setShortcut(QKeySequence("Ctrl+Q"));
      ui->actionQuitter_3->setIcon(QIcon("C:\\Users\\sony\\Projets\\Gestion-Financiere\\Gestion\\Icons\\quitter.png"));
     connect(ui->actionChanger_la_couleur_du_texte,SIGNAL(triggered()),this,SLOT(changerCouleurText()));
    connect(ui->actionQuitter_3,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionA_propos,SIGNAL(triggered()),this,SLOT(aPropos()));
    connect(ui->actionChanger_la_couleur_de_l_arrier_plan,SIGNAL(triggered()),this,SLOT(ouvrirPalette()));
    connect(ui->actionChanger_la_couleur_de_texte,SIGNAL(triggered()),this,SLOT(ouvrirPolice()));
    connect(ui->actionTheme_couscous,SIGNAL(triggered()),this,SLOT(changerTheme()));
    connect(ui->actionTheme100Drh,SIGNAL(triggered()),this,SLOT(changerTheme2()));
    connect(ui->actionTheme50dh,SIGNAL(triggered()),this,SLOT(changerTheme1()));
    connect(ui->actionThem_euro,SIGNAL(triggered()),this,SLOT(changerTheme3()));
    connect(ui->actionImprimer,SIGNAL(triggered()),this,SLOT(imprimer()));



}

void MainWindow::ouvrirPalette()
{
    QColor couleur = QColorDialog::getColor(Qt::white, this);
    QPalette palette;

    palette.setColor(QPalette::Background, couleur);
    this->setPalette(palette);
}
void MainWindow::ouvrirPolice()
{

    bool ok = false;
    QFont police = QFontDialog::getFont(&ok,this->font(), this, "Choisissez une police");
    if (ok)
    {
    this->setFont(police);
    }


}
void MainWindow::ouvrirDialogue()
{
 int reponse = QMessageBox::question(this, "Fin", "Etes-vous sûr(e) de vouloir quitter ?", QMessageBox::Yes | QMessageBox::No);


    if (reponse == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Quitter", "L'application va se fermé!");
        close();
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::information(this, "Continuer", "Vous avez decider de ne pas fermer l'application ");
    }
}
 void MainWindow::changerCouleurText(){

     QColor couleur = QColorDialog::getColor(Qt::white, this);
     QPalette palette;

     palette.setColor(QPalette::ButtonText, couleur);
    this->setPalette(palette);




 }
void MainWindow::changerTheme(){
    QPalette palette;
   palette.setBrush(this->backgroundRole(), QBrush(QImage("C:\\Users\\sony\\Projets\\Gestion-Financiere\\Gestion\\Icons\\pp1.jpg")));
    this->setPalette(palette);
     this->setAutoFillBackground( true );
}
void MainWindow::changerTheme1(){

    QPalette palette;
   palette.setBrush(this->backgroundRole(), QBrush(QImage("C:\\Users\\sony\\Projets\\Gestion-Financiere\\Gestion\\Icons\\502.jpg")));
    this->setPalette(palette);
     this->setAutoFillBackground( true );


}
void MainWindow::changerTheme2(){

    QPalette palette;
   palette.setBrush(this->backgroundRole(), QBrush(QImage("C:\\Users\\sony\\Projets\\Gestion-Financiere\\Gestion\\Icons\\6.jpg")));
    this->setPalette(palette);
     this->setAutoFillBackground( true );


}
void MainWindow::changerTheme3(){

    QPalette palette;
   palette.setBrush(this->backgroundRole(), QBrush(QImage("C:\\Users\\sony\\Projets\\Gestion-Financiere\\Gestion\\Icons\\i.jpg")));
    this->setPalette(palette);
     this->setAutoFillBackground( true );


}
void MainWindow::imprimer(){



    QPrinter *printer = new QPrinter();
    printer->setPaperSize(QPrinter::A4);
    printer->setFullPage(true);

    QPrintDialog *dialog = new QPrintDialog(printer,0);

    dialog->setWindowTitle(tr("Imprimer Document"));

    if (dialog->exec() != QDialog::Accepted)
        return;

   ui->textBrowser->print(printer);

}
QString MainWindow::traitementEntite(){
    QString t1="";
                 if (!db.open()){
                    QMessageBox::critical(0, QObject::tr("Database Error"),
                                          db.lastError().text());
                }
                else {
                    QSqlQuery query,quer;
                    QString q = "SELECT * FROM entite ";

                    query.exec(q);
                        QString id;
          while(query.next()) {
              QString tt=""; QString tR="";
                            id = query.value(0).toString();
                            tt+="\tNom Entite :" +query.value(1).toString();
                            tR+="\tNom Reponsable :" + query.value(2).toString();
                            q = "SELECT  id_rubrique,budget,consomme FROM budget WHERE id_entite='"+id+"'";
                            query.exec(q);
                                QString tr="";
                                QString nom,rubrique, budget, consomme,restant;
                                int budgetGlob=0,budgetCons=0,budgetRest=0;
                                while(query.next()) {
                                    rubrique = query.value(0).toString();
                                    budget = query.value(1).toString();
                                    consomme = query.value(2).toString();
                                    restant = QString::number( query.value(1).toInt()- query.value(2).toInt());

                                    budgetGlob += query.value(1).toInt();
                                    budgetCons += query.value(2).toInt();
                                    budgetRest += query.value(1).toInt()- query.value(2).toInt();


                                 QString req= "SELECT nom FROM rubrique WHERE id='"+rubrique+"'";
                                        quer.exec(req);quer.next();
                                        nom= quer.value(0).toString();
                                        tr+="\n Nom Rubrique: " + nom +"\t Budget de la rubrique: "+ budget + " Consmmation : "+ consomme +"\t Restant  :  " + restant +"\n";
                                     }
                                t1+=tt + tR  +"\n" ;
       t1+="\tBudget Global:  " +QString::number(budgetGlob)+ " \tBudget total Consommé: "+ QString::number(budgetCons)+ " \t   Total Restant:"+QString::number( budgetRest) + "\n" ;
       t1+=tr ;
       t1+="-------------------------------------------------------------------------------------------------------------------------\n";

                        }
          }
            return t1;


    }
QString  MainWindow::traitemententRubrique(){

    QString tr="";
                 if (!db.open()){
                    QMessageBox::critical(0, QObject::tr("Database Error"),
                                          db.lastError().text());
                }
                else {
                    QSqlQuery query;
                    QString q = "SELECT nom FROM rubrique ";

                    query.exec(q);

          while(query.next()) {
              QString nom= query.value(0).toString();
    Rubrique *rubrique = new Rubrique(nom);

    tr+="Nom Rubrique " + nom +" \t Budget : " +  rubrique->getBudget() + "\n";

    tr+="Budget Global : "  + rubrique->getBudgetGlob() + "\t Budget Consommé : " +  rubrique->getBudgetCons();
    tr+=" \t  Budget Restant  : " + rubrique->getBudgetRest();

   }
}

   return tr ;

}



void MainWindow::on_pushButton_7_clicked()
{
    QString text="";
             text +="\t\t\t ETAT BUDGETAIRE \n" ;
             text+="\t********************************************************************** \n";
             text+="\t Nom de L'etabilssement         \t    \t  \t Budget Global    \n" ;
    QString text1 = "";
    QString text2 ="" ;
    QString text3 ="" ;
    // Connexion à la base de données
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("alizetas");
    if (!db.open()){
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
    }
     else {

         QSqlQuery query,querG,quer;
           QString q=" select budgetGlobal  ,etablissement  from general ";
           querG.exec(q);
           while(querG.next()){
               text1 +="\t" +querG.value(1).toString()+" \t\t\t "+querG.value(0).toString()+"\n";
                }
  text1+="\t-------------------------------------------------------------------------------------------------\n";
  text1+="\t\t\tCONSOMMATION \n ";
  text1+="\tFournisseur \t\tCommande  \t\tDate de  Livraison  \n";

         QString qid = "SELECT fournisseur ,commentaire ,date FROM  consommation ";
             query.exec(qid);
             while(query.next()){
                 text2 +="\t" +query.value(0).toString()+"\t\t"+query.value(1).toString()+"\t\t"+query.value(2).toString()+"\n" ;

             }
              text2+="\t-------------------------------------------------------------------------------------------------\n";
              text2+="\t\t\tEtat budgetaire des entités \n ";
              text2+=traitementEntite();
              text2+="\t-------------------------------------------------------------------------------------------------\n";
              text2+="\t\t\tEtat budgetaire des Rubriques\n ";
              text2+=traitemententRubrique();


             text += text1 +text2 ;
              ui->textBrowser->setText(text);
    }
}
