#include <QApplication>
#include "sdes.h"
#include "Window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window w;
    w.show();

    return a.exec();
}
