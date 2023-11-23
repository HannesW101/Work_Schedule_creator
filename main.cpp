#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Set the window icon
    QIcon icon("://images/WindowIcon.png");
    w.setWindowIcon(icon);

    // Remove the status bar
    w.setStatusBar(0);

    // Set the window title
    w.setWindowTitle(" ");

    w.show();
    return a.exec();
}
