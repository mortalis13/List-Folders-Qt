
#include <QMetaObject>

#include "tnmodel.h"

TNModel::TNModel(TN *root, QObject *parent) : QAbstractItemModel( parent )
{
  m_root = root;
}

Qt::ItemFlags TNModel::flags(const QModelIndex &index) const{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TNModel::data(const QModelIndex &index, int role) const{
  if( !index.isValid() ){
    return QVariant();
  }

  if( role == Qt::DisplayRole ){
    switch( index.column() ){
    case 0:
       return "text";
    default:
      break;
    }
  }
  
  return QVariant();
}

int TNModel::rowCount(const QModelIndex &parent) const{
  TN *parentObject;

  if( !parent.isValid() ){
    parentObject = m_root;
  }
  else{
    parentObject = static_cast<TN*>( parent.internalPointer() );
  }

  int rows=parentObject->m_children->size();
  return rows;
}

int TNModel::columnCount(const QModelIndex &parent) const{
  return 1;
}

QModelIndex TNModel::index(int row, int column, const QModelIndex &parent) const{
  TN *parentObject;

  if( !parent.isValid() ){
    parentObject = m_root;
  }
  else{
    parentObject = static_cast<TN*>( parent.internalPointer() );
  }

  if( row < parentObject->m_children->size() ){
    TN* child=parentObject->m_children->at(row);
    return createIndex( row, column, child );
  }
  else{
    return QModelIndex();
  }
}

QModelIndex TNModel::parent(const QModelIndex &index) const{
  if( !index.isValid() ){
    return QModelIndex();
  }

  TN *indexObject = static_cast<TN*>( index.internalPointer() );
  TN *parentObject = indexObject->m_parent;

  if( parentObject == m_root )
    return QModelIndex();

  TN *grandParentObject = parentObject->m_parent;
  return createIndex( grandParentObject->m_children->indexOf( parentObject ), 0, parentObject );
}
