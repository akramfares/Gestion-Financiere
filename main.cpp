#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("atlasteam");
        db.setUserName("root");
        db.setPassword("");
        if (!db.open()){
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  db.lastError().text());
        }
        else {
            QSqlQuery query;
                query.exec("SELECT login, nom FROM user_profile");
                QString s=query.lastError().text();
                while(query.next()) {
                    s += query.value(0).toString();
                    s +=" h" + query.value(1).toString();
                }
                QMessageBox::critical(0, QObject::tr("Database Error"),s);
        }

    return a.exec();
}
