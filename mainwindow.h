#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_comboBox_3_currentIndexChanged(const QString &arg1);
    void setTableEntite(QString nom);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
