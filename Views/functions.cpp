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
