#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

#include "Models/Tree/dirnode.h"

class TreeModel : public QAbstractItemModel
{
public:
  explicit TreeModel(DirNode* root, QObject *parent = 0);

  // overridden

  Qt::ItemFlags flags( const QModelIndex &index ) const;
  QVariant data( const QModelIndex &index, int role ) const;

  QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
  QModelIndex parent( const QModelIndex &index ) const;
  
  int rowCount( const QModelIndex &parent = QModelIndex() ) const;
  int columnCount( const QModelIndex &parent = QModelIndex() ) const;
  
  // custom
  
  DirNode *getRoot();
  
private:
  DirNode *m_root;
  QString iconsPath;
  
  void prepareIcons();
};

#endif // TREEMODEL_H
