#include <QtGui/QApplication>
#include "tictactoe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicTacToe w;
    w.show();
    //QString myPath;
      //  myPath = "./imageformats";
        //a.addLibraryPath(myPath);

    //Q_INIT_RESOURCE(icons);
   return a.exec();
}
