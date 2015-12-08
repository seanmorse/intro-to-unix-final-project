
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <QWidgetList>
#include <QTextEdit>
#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
int main( int argc, char ** argv ) {

    QApplication a(argc,argv);

    MainWindow main;

    main.show();

    /*if(main.error>0)
    {
        return 0;
    }*/
    return a.exec();
}

