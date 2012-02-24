#include "admindialog.h"
#include "ui_admindialog.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    // Connexion à la base de données
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestionfinanciere");
    db.setUserName("root");
    db.setPassword("");

    // Initialisation des combos
    Rubrique *rubrique = new Rubrique("");
    ui->comboSearchRubrique->addItem("");
    rubrique->initComboAll(ui->comboSearchRubrique);
}

AdminDialog::~AdminDialog()
{
    delete ui;
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
    if(rubrique->exists()){
        QMessageBox::critical(0, QObject::tr("Erreur"),
                              "Cette Rubrique éxiste déjà !");
        return;
    }

    // On ajoute la rubrique à la base de données
    rubrique->addRubrique(ui->nomRubrique->text(), ui->bdgTotalRubrique->text());
    // On ajoute la rubrique au comboBox
    ui->comboSearchRubrique->addItem(ui->nomRubrique->text());
    // On positionne le curseur sur la nouvelle Rubrique
    int ci = ui->comboSearchRubrique->count();
    ui->comboSearchRubrique->setCurrentIndex(ci - 1);
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

    // On ajoute la rubrique à la base de données
    rubrique->editRubrique(ui->comboSearchRubrique->currentText(), ui->nomRubrique->text(), ui->bdgTotalRubrique->text());
    //On modifie le nom de la Rubrique dans le ComboBox
    int ci = ui->comboSearchRubrique->currentIndex();
    ui->comboSearchRubrique->setItemText(ci,ui->nomRubrique->text());
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

}
// Quand on choisi une entité de rubrique
void AdminDialog::on_comboEntiteRubrique_currentIndexChanged(const QString &arg1)
{
    // Si une entité est sélectionnée
    if(ui->comboSearchRubrique->currentIndex()!=0){
        Rubrique *rubrique = new Rubrique(ui->comboSearchRubrique->currentText());
        QString budget = rubrique->getBudgetParEntite(arg1, ui->addBudgetRubrique);
        // On modifie le champ budget par entité
        ui->bdgParEntite->setText(budget);
    }
}
// Bouton ajouter un budget par entité
void AdminDialog::on_addBudgetRubrique_clicked()
{
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
    }
    else {
        if(ui->comboSearchRubrique->currentText().isEmpty()){
            QMessageBox::critical(0, QObject::tr("Erreur"),
                                  "Veuillez choisir une Rubrique et une Entité !");
            return;
        }
    }
}
