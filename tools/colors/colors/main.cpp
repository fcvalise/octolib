#include "PaletteEditor.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaletteEditor w;
    w.show();

    return a.exec();
}
