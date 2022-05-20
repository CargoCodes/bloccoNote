#include "GUInterface.h"
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    GUInterface GUI;
    GUI.show();
    app.exec();
}
