#include "passwordgen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PassWordGen w;
    w.show();

    return a.exec();
}
