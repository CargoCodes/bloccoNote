#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    GUI GUI;
    GUI.show();
    app.exec();
}
