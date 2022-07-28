#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 mainWindow window;
 window.setFixedSize(640,480);

 srand (time(NULL));

 window.show();

 return app.exec();
}
