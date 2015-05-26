
#ifndef TESTTREEMODEL_H
#define TESTTREEMODEL_H

#include <QAbstractItemModel>
#include "test.h"

class TestTreeModel : public QAbstractItemModel
{
public:
  TestTreeModel( Test *root, QObject *parent = 0 );
  
  Qt::ItemFlags flags( const QModelIndex &index ) const;
  QVariant data( const QModelIndex &index, int role ) const;
  int rowCount( const QModelIndex &parent = QModelIndex() ) const;
  int columnCount( const QModelIndex &parent = QModelIndex() ) const;
  
  QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
  QModelIndex parent( const QModelIndex &index ) const;
  
private:
  Test *m_root;
};

#endif // TESTTREEMODEL_H
