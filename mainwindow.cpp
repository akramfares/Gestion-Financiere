#include "mainwindow.h"
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
                QSqlQuery query;
                QString q = "SELECT * FROM entite WHERE nom LIKE '";
                q.append(nom);
                q.append("'");
                    query.exec(q);
                    QString id;
                    while(query.next()) {
                        id = query.value(0).toString();
                    }

                q = "SELECT id_rubrique,budget,consomme FROM budget WHERE id_entite='";
                q.append(id);
                q.append("'");
                    query.exec(q);
                    int count=0;
                    QString rubrique, budget, consomme;
                    while(count<query.size()-1) {
                        query.next();
                        rubrique = query.value(0).toString();
                        budget = query.value(1).toString();
                        consomme = query.value(2).toString();

                        ui->tableEntite->insertRow(count);
                        QTableWidgetItem *r = new QTableWidgetItem;
                        r->setText(rubrique);
                        ui->tableEntite->setItem(0,0,r);
                        QTableWidgetItem *bc = new QTableWidgetItem;
                        bc->setText(budget);
                        ui->tableEntite->setItem(0,1,bc);
                        QTableWidgetItem *br = new QTableWidgetItem;
                        br->setText(consomme);
                        ui->tableEntite->setItem(0,2,br);
                        count++;
                    }


            }

}
