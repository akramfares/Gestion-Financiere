#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H


#include <QDialog>
#include <rubrique.h>
#include <consommation.h>
#include <general.h>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


namespace Ui {
    class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = 0);
    void  rechercherEntite(QString nom);
    void changeTheme();
    ~AdminDialog();


private slots:
    void on_addButtonEntite_clicked();

    void on_editButtonEntite_clicked();

    void on_delButtonEntite_clicked();

    void on_comboSearchEntite_currentIndexChanged(const QString &arg1);
    void on_comboSearchRubrique_currentIndexChanged(const QString &arg1);

    void on_addButtonRubrique_clicked();

    void on_editButtonRubrique_clicked();

    void on_delButtonRubrique_clicked();

    void on_comboEntiteRubrique_currentIndexChanged(const QString &arg1);

    void on_addBudgetRubrique_clicked();

    void on_saveButtonCons_clicked();

    void on_saveGeneral_clicked();


private:
    Ui::AdminDialog *ui;
     QSqlDatabase db;
     Rubrique *rubrique;
};
#endif // ADMINDIALOG_H
