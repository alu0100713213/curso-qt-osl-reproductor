#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Music and Video Player");
    a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();
    
    return a.exec();
}
