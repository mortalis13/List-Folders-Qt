#include "Views/mainwindow.h"
#include <Controllers/controller.h>
#include <Models/model.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow view;
    Model model;
    Controller controller(view, model);

    view.setController(controller);
    view.show();

    return a.exec();
}
