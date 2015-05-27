#ifndef FILENODE_H
#define FILENODE_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

#include "Models/Tree/treenode.h"
#include "Models/Tree/dirnode.h"

class FileNode : public TreeNode
{
public:
    FileNode(QString text, QString icon);
    void write(QJsonObject &json) const;
    void setParent(DirNode *parent);
};

#endif // FILENODE_H
