#include "Views/functions.h"
#include "ui_mainwindow.h"

Functions::Functions(QObject *parent) :
    QObject(parent)
{
}

/*
 * Gets Dictionary of all form fields
 * which is used to serialize them to JSON string
 */
QHash<QString, QVariant> Functions::getFieldsMap(Ui::MainWindow* ui) {
    QHash<QString, QVariant> dict;

    QString path, filterExt, excludeExt, filterDir, exportName;
    bool doExportText, doExportTree;
    
    path = ui->lePath->text();
    filterExt = ui->teFilterExt->toPlainText();
    excludeExt = ui->teExcludeExt->toPlainText();
    filterDir = ui->teFilterDir->toPlainText();

    doExportText = ui->chExportText->isChecked();
    doExportTree = ui->chExportTree->isChecked();
    exportName = ui->leExportName->text();
    
    dict.insert("path", path);
    dict.insert("filterExt", filterExt);
    dict.insert("excludeExt", excludeExt);
    dict.insert("filterDir", filterDir);
    dict.insert("doExportText", doExportText);
    dict.insert("doExportTree", doExportTree);
    dict.insert("exportName", exportName);

    return dict;
}

void Functions::loadConfig(Ui::MainWindow* ui, const QHash<QString, QVariant> &fields)
{
  ui->lePath->setText(fields["path"].toString());
  ui->teFilterExt->setPlainText(fields["filterExt"].toString());
  ui->teExcludeExt->setPlainText(fields["excludeExt"].toString());
  ui->teFilterDir->setPlainText(fields["filterDir"].toString());

  ui->chExportText->setChecked(fields["doExportText"].toBool());
  ui->chExportTree->setChecked(fields["doExportTree"].toBool());
  ui->leExportName->setText(fields["exportName"].toString());
}

void Functions::setProgress(Ui::MainWindow* ui, int progress){
  ui->progressBar->setValue(progress);
}

void Functions::log(Ui::MainWindow* ui, const QString &text){
  ui->teOut->appendPlainText(text);
}

void Functions::clearLog(Ui::MainWindow* ui){
  ui->teOut->clear();
}

QString Functions::formatTime(int time, QString format)
{
  QString res;
  return res.sprintf(qPrintable(format), (float)time / 1000);
}
