#include "GUI.h"
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    GUI GUI;
    GUI.show();
    app.exec();
}
