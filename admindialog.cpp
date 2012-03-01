#include "admindialog.h"
#include "ui_admindialog.h"
#include "gestionentite.h"
#include"mainwindow.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
     GestionEntite *ges = new GestionEntite("");
     ges->misjajourComboxRecherche(ui->comboSearchEntite);
     db = QSqlDatabase::addDatabase("QMYSQL");
     db.setHostName("localhost");
     db.setDatabaseName("gestionfinanciere");
     db.setUserName("root");
     db.setPassword("alizetas");

/////////////////////////////////////////////////////////////////////////////////////////////
     // Initialisation des combos
     Rubrique *rubrique = new Rubrique("");
     ui->comboSearchRubrique->addItem("");
     rubrique->initComboAll(ui->comboSearchRubrique);

     // On masque le formulaire de consommation
     ui->groupConsommation->hide();
     // On masque l'idBudget
     ui->idBudget->hide();

     // Mise à jour des infos généraux
     General *general = new General();
     general->updateInfos(ui->etablissement,ui->bdgGlobal,ui->login);
     //Gestion des boutons
     connect(ui->quitter,SIGNAL(clicked()),this,SLOT(close()));

}



void AdminDialog::on_addButtonEntite_clicked()
{


    GestionEntite *ges = new GestionEntite("");
        ges->ajouterEntite(ui->nomEntite,ui->respEntite);



}

void AdminDialog::on_editButtonEntite_clicked()
{

    GestionEntite *ges = new GestionEntite("");
        ges->modifierEntite(ui->nomEntite,ui->respEntite);

}

void AdminDialog::on_delButtonEntite_clicked()
{

    GestionEntite *ges = new GestionEntite("");
        ges->deleteEntite(ui->nomEntite);

}

void AdminDialog::on_comboSearchEntite_currentIndexChanged(const QString &arg1)
{
    GestionEntite *ges = new GestionEntite("");
    ui->nomEntite->setText(arg1);

     ui->respEntite->setText(ges->getNomResponsable(arg1));
      ui->bdgTotalEntite->setText(ges->getBudgetGlob(arg1));

    ges->misjajourComboxRecherche(ui->comboSearchEntite);

}
void AdminDialog::on_saveGeneral_clicked()
{
    General *general = new General();
    general->setInfos(ui->etablissement->text(),ui->bdgGlobal->text(),ui->login->text(),ui->newPassword->text());
    QMessageBox::information(0, QObject::tr("Général"),
                          "Informations mise à jour avec succès !");
}
void AdminDialog::on_comboSearchRubrique_currentIndexChanged(const QString &arg1)
{
    Rubrique *rubrique = new Rubrique(arg1);
    ui->nomRubrique->setText(arg1);
    ui->bdgTotalRubrique->setText(rubrique->getBudget());
    rubrique->initComboEntite(ui->comboEntiteRubrique);
}

// Ajouter une Rubrique
void AdminDialog::on_addButtonRubrique_clicked()
{

    Rubrique *rubrique = new Rubrique(ui->nomRubrique->text());
    if(ui->nomRubrique->text().isEmpty()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter un nom de Rubrique !");
        return;
    }
    if(ui->bdgTotalRubrique->text().isEmpty()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter un budget de Rubrique !");
        return;
    }
    bool ok;
    ui->bdgTotalRubrique->text().toInt(&ok);
    if(!ok){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter un budget valide !");
        return;
    }
    if(rubrique->exists()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Cette Rubrique éxiste déjà !");
        return;
    }

    // On ajoute la rubrique à la base de données
    rubrique->addRubrique(ui->nomRubrique->text(), ui->bdgTotalRubrique->text());
    //ui->nomRubrique->setText(""), ui->bdgTotalRubrique->setText("");
    // On ajoute la rubrique au comboBox
    ui->comboSearchRubrique->addItem(ui->nomRubrique->text());
    // On positionne le curseur sur la nouvelle Rubrique
    int ci = ui->comboSearchRubrique->count();
    ui->comboSearchRubrique->setCurrentIndex(ci - 1);

    QMessageBox::information(0, QObject::tr("Rubrique"),
                          "Rubrique ajoutée avec succès !");
}
// Editer une Rubrique
void AdminDialog::on_editButtonRubrique_clicked()
{
    Rubrique *rubrique = new Rubrique(ui->nomRubrique->text());
    if(ui->comboSearchRubrique->currentText().isEmpty()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez choisir une Rubrique !");
        return;
    }
    if(ui->nomRubrique->text().isEmpty()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter un nom de Rubrique !");
        return;
    }
    if(ui->bdgTotalRubrique->text().isEmpty()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter un budget de Rubrique !");
        return;
    }

    bool ok;
    ui->bdgTotalRubrique->text().toInt(&ok);
    if(!ok){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter un budget valide !");
        return;
    }

    // On ajoute la rubrique à la base de données
    rubrique->editRubrique(ui->comboSearchRubrique->currentText(), ui->nomRubrique->text(), ui->bdgTotalRubrique->text());
    //On modifie le nom de la Rubrique dans le ComboBox
    int ci = ui->comboSearchRubrique->currentIndex();
    ui->comboSearchRubrique->setItemText(ci,ui->nomRubrique->text());

    QMessageBox::information(0, QObject::tr("Rubrique"),
                          "Rubrique modifiée avec succès !");
}
// Bouton supprimer
void AdminDialog::on_delButtonRubrique_clicked()
{
    int validation = QMessageBox::question(this, "Suppresion", "Voulez-vous vraiment supprimer cette rubrique?", QMessageBox::Yes | QMessageBox::No);
    if(validation == QMessageBox::No){
        return;
    }

    if(ui->comboSearchRubrique->currentText().isEmpty()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez choisir une Rubrique !");
        return;
    }
    Rubrique *rubrique = new Rubrique(ui->nomRubrique->text());
    // Supprimer la rubrique
    rubrique->deleteRubrique(ui->comboSearchRubrique->currentText());
    // Supprimer la rubrique du combobox
    int ci = ui->comboSearchRubrique->currentIndex();
    ui->comboSearchRubrique->removeItem(ci);
    // Positionner le curseur sur le premier élément qui est vide
    ui->comboSearchRubrique->setCurrentIndex(0);
    // Vider les champs
    ui->nomRubrique->setText("");
    ui->bdgTotalRubrique->setText("");

    QMessageBox::information(0, QObject::tr("Rubrique"),
                          "Rubrique supprimée avec succès !");

}
// Quand on choisi une entité de rubrique
void AdminDialog::on_comboEntiteRubrique_currentIndexChanged(const QString &arg1)
{
    // Si une entité est sélectionnée
    if(ui->comboSearchRubrique->currentIndex()!=0){
        Rubrique *rubrique = new Rubrique(ui->comboSearchRubrique->currentText());
        QString budget = rubrique->getBudgetParEntite(arg1, ui->addBudgetRubrique, ui->groupConsommation, ui->idBudget);
        // On modifie le champ budget par entité
        ui->bdgParEntite->setText(budget);
    }
}
// Bouton ajouter un budget par entité
void AdminDialog::on_addBudgetRubrique_clicked()
{
    bool ok;
    ui->bdgParEntite->text().toInt(&ok);
    if(!ok){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter un budget valide !");
        return;
    }

    // Si une rubrique et une entité sont sélectionnés
    if(ui->comboSearchRubrique->currentIndex()!=0 && ui->comboEntiteRubrique->currentIndex()!=0){
        Rubrique *rubrique = new Rubrique(ui->comboSearchRubrique->currentText());
        // Si le bouton est pour ajouter
        if(ui->addBudgetRubrique->text()=="Ajouter Budget") {
            ui->addBudgetRubrique->setText("Modifier Budget");
            rubrique->addBudgetEntite(ui->comboEntiteRubrique->currentText(), ui->bdgParEntite->text());
        }
        // Si le bouton est pour modifier
        else if(ui->addBudgetRubrique->text()=="Modifier Budget"){
            rubrique->editBudgetEntite(ui->comboEntiteRubrique->currentText(), ui->bdgParEntite->text());
        }

        QMessageBox::information(0, QObject::tr("Rubrique"),
                              "Budget ajouté avec succès !");
    }
    else {
        if(ui->comboSearchRubrique->currentText().isEmpty()){
            QMessageBox::critical(0, QObject::tr("Erreur"),
                                  "Veuillez choisir une Rubrique et une Entité !");
            return;
        }
    }
}
// Bouton pour ajouter une consommation
void AdminDialog::on_saveButtonCons_clicked()
{
    if(ui->consommation->text().isEmpty()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter une consommation !");
        return;
    }
    bool ok;
    ui->consommation->text().toInt(&ok);
    if(!ok){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter une consommation valide !");
        return;
    }

    if(ui->fournisseur->text().isEmpty()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Veuillez ajouter un fournisseur !");
        return;
    }

    // Vérification de la condition de validation
    Consommation *consom = new Consommation(ui->idBudget->text());
    if(!consom->isValid(ui->consommation->text())){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Vous avez atteint la limite de consommation !");
        return;
    }

    QMessageBox::information(0, QObject::tr("Consommation"),
                          "Consommation ajoutée avec succès !");
    // Ajout de la consommation
    consom->addConsommation(ui->consommation->text(), ui->fournisseur->text(), ui->commentaire->toPlainText());
    ui->consommation->setText(""); ui->fournisseur->setText(""); ui->commentaire->setText("");
}




AdminDialog::~AdminDialog()
{
    delete ui;
}


