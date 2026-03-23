#include "mainwindow.h"

#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Proyecto Buscaminas");
    QApplication::setApplicationName("Proyecto_Buscaminas");
    QApplication::setApplicationDisplayName("Buscaminas");
    QApplication::setApplicationVersion("0.1.0");
    MainWindow w;
    w.show();
    return a.exec();
}
