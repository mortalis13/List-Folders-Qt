#ifndef TNMODEL_H
#define TNMODEL_H

#include <QAbstractItemModel>

// #include "Models/tn.h"
#include "Views/tn.h"

class TNModel : public QAbstractItemModel
{
public:
  explicit TNModel(TN* root, QObject *parent = 0);

  Qt::ItemFlags flags( const QModelIndex &index ) const;
  QVariant data( const QModelIndex &index, int role ) const;
  int rowCount( const QModelIndex &parent = QModelIndex() ) const;
  int columnCount( const QModelIndex &parent = QModelIndex() ) const;

  QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
  QModelIndex parent( const QModelIndex &index ) const;

private:
  TN *m_root;

};

#endif // TNMODEL_H
