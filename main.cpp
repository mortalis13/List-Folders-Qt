#include <QApplication>

#include "Models/model.h"
#include "Views/mainwindow.h"
#include "Controllers/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model model;
    MainWindow view(model);
    Controller controller(view, model);

    view.setController(controller);
    view.show();
    view.loadConfig();                      // loads last saved config (field values) from the database (SQLite local .db file)

    return a.exec();
}
