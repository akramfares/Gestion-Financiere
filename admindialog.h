#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <rubrique.h>
#include <entite.h>

namespace Ui {
    class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = 0);
    ~AdminDialog();

private slots:
    void on_comboSearchRubrique_currentIndexChanged(const QString &arg1);

    void on_addButtonRubrique_clicked();

    void on_editButtonRubrique_clicked();

    void on_delButtonRubrique_clicked();

    void on_comboEntiteRubrique_currentIndexChanged(const QString &arg1);

    void on_addBudgetRubrique_clicked();

private:
    Ui::AdminDialog *ui;
    QSqlDatabase db;
    Rubrique *rubrique;
};

#endif // ADMINDIALOG_H
