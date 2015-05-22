#include "Views/mainwindow.h"
#include <Controllers/controller.h>
#include <Models/model.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model model;

    MainWindow view(model);
//    MainWindow *view=new MainWindow(model);

    Controller controller(view, model);

    view.setController(controller);
    view.show();

    view.init();

    return a.exec();
}
