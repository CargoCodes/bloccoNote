#include "MainWindow.h"
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow GUI;
    GUI.show();
    app.exec();
}
