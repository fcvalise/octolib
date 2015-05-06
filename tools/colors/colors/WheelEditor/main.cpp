#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("WheelEditor");
    QApplication::setApplicationDisplayName("Wheel Editor");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("Octo Team");

    MainWindow w;
    w.show();
    return a.exec();
}
