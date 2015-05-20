#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QObject>

namespace Ui {
class MainWindow;
}

class Functions : public QObject
{
    Q_OBJECT
public:
    explicit Functions(QObject *parent = 0);

    static QHash<QString, QVariant> getFieldsMap(Ui::MainWindow *ui);
signals:

public slots:

};

#endif // FUNCTIONS_H
