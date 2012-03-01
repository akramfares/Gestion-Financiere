#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QMainWindow>
#include "AdminDialog.h"
#include "general.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
     void misjajourComboxRubrique();
      void misjajourResponsable();
      void gestionMenu();
      QString traitementEntite();
      QString traitemententRubrique();

    ~MainWindow();

private slots:

    void on_comboBox_3_currentIndexChanged(const QString &arg1);
    void setTableEntite(QString nom);
    void setTableRubrique(QString nom);
    void initCombos();

    void on_comboRubrique_currentIndexChanged(const QString &arg1);

   // void on_adminConnect_clicked();


    void on_adminConnect_clicked();





    void ouvrirDialogue();
    void aPropos();
    void ouvrirPolice();
    void ouvrirPalette();
    void changerCouleurText();
    void changerTheme();
    void changerTheme1();
    void changerTheme2();
    void changerTheme3();
    void imprimer();


    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
