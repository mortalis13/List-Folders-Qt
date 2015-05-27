#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QObject>

namespace Ui {
class MainWindow;
}

class Functions : public QObject
{
public:
  explicit Functions(QObject *parent = 0);

  static QHash<QString, QVariant> getFieldsMap(Ui::MainWindow *ui);
  static QString formatPath(QString path);
  static void clearLog(Ui::MainWindow *ui);
  static void setProgress(Ui::MainWindow *ui, int progress);
  static void log(Ui::MainWindow *ui, const QString &text);
  static QString formatTime(int time, QString format);
  static void loadConfig(Ui::MainWindow *ui, const QHash<QString, QVariant> &fields);

};

#endif // FUNCTIONS_H
