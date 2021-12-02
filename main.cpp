#include "widget.h"
#include <QTextStream>
#include <QInputDialog>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget window;
    window.setWindowTitle("Handler of lower triangular numerical matrices");
    window.resize(230, 230);
    window.show();

    return a.exec();
}
