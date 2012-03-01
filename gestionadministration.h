#ifndef GESTIONADMINISTRATION_H
#define GESTIONADMINISTRATION_H
#include<QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "mainwindow.h"

class GestionAdministration:public MainWindow
{
  Q_OBJECT
public:
    GestionAdministration( QWidget *parent);
  void on_bouton_connecter_currentIndexChanged(const QString &arg1);
  void  setTableGestion(QString nom);
  QString requete_insertion_entite( QString name,QString nameOfresp);
  QString requete_suppression_entite(QString name);
  QString requete_mis_a_jour_entite(QString id,QString name , QString nameofresp);
  QString requete_insertion_rubrique();
  QString requete_suppression_rubrique();
  QString requete_mis_a_jour_rubrique();
  QString  requete_affichage_info_enite();
  QString requete_affichage_info_rubrique();







};

#endif // GESTIONADMINISTRATION_H
