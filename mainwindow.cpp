#include "mainwindow.h"
#include <sstream>
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QString>
#include <QMessageBox>
#include <QTableWidgetItem>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BarreOutils->removeTab(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    QMessageBox::information(0, QObject::tr("Ajouter une Entité"),arg1);
    ui->BarreOutils->insertTab(1,ui->tabEntite,"Entité");
    ui->BarreOutils->setCurrentIndex(1);
    setTableEntite(arg1);
}

void MainWindow::setTableEntite(QString nom){

    ui->tableEntite->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

            db.setHostName("localhost");
            db.setDatabaseName("gestionfinanciere");
            db.setUserName("root");
            db.setPassword("");
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
                    QString nom,rubrique, budget, consomme,restant="";
                    while(count<query.size()) {
                        query.next();
                        rubrique = query.value(0).toString();
                        budget = query.value(1).toString();
                        consomme = query.value(2).toString();



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

}
