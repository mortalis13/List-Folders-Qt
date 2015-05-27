#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "Models/Tree/dirnode.h"
#include "Models/Tree/treenode.h"
#include "Models/Tree/filenode.h"

class TreeModel : public QAbstractItemModel
{
public:
  explicit TreeModel(DirNode* root, QObject *parent = 0);

  Qt::ItemFlags flags( const QModelIndex &index ) const;
  QVariant data( const QModelIndex &index, int role ) const;
  int rowCount( const QModelIndex &parent = QModelIndex() ) const;
  int columnCount( const QModelIndex &parent = QModelIndex() ) const;

  QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
  QModelIndex parent( const QModelIndex &index ) const;

  DirNode *getRoot();
private:
  DirNode *m_root;
  QString iconsPath;
//  QList<QIcon> icons;
  void prepareIcons();
};

#endif // TREEMODEL_H
