#include <QApplication>
#include "View/mainview.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    s21::Model model;
    s21::Controller controller(&model);
    s21::MainView view(&controller);
    view.startEventLoop();
    return app.exec();
}
