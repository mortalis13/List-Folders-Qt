
#include <QMetaObject>

#include "objecttreemodel.h"

ObjectTreeModel::ObjectTreeModel( QObject *root, QObject *parent ) : QAbstractItemModel( parent )
{
  m_root = root;
}

Qt::ItemFlags ObjectTreeModel::flags(const QModelIndex &index) const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ObjectTreeModel::data( const QModelIndex &index, int role) const
{
  if( !index.isValid() )
    return QVariant();

  if( role == Qt::DisplayRole )
  {
    switch( index.column() )
    {
    case 0:
      return static_cast<QObject*>( index.internalPointer() )->objectName();
    default:
      break;
    }
  }
  else if( role == Qt::ToolTipRole )
  {
    switch( index.column() )
    {
    case 0:
      return QString( "The name of the object." );
    default:
      break;
    }
  }

  return QVariant();
}

int ObjectTreeModel::rowCount(const QModelIndex &parent ) const
{
  QObject *parentObject;
  
  if( !parent.isValid() )
    parentObject = m_root;
  else
    parentObject = static_cast<QObject*>( parent.internalPointer() );

  return parentObject->children().count();
}

int ObjectTreeModel::columnCount(const QModelIndex &parent ) const
{
  return 1;
}

QModelIndex ObjectTreeModel::index(int row, int column, const QModelIndex &parent ) const
{
  QObject *parentObject;
  
  if( !parent.isValid() )
    parentObject = m_root;
  else
    parentObject = static_cast<QObject*>( parent.internalPointer() );
  
  if( row < parentObject->children().count() )
    return createIndex( row, column, parentObject->children().at( row ) );
  else
    return QModelIndex();
}

QModelIndex ObjectTreeModel::parent(const QModelIndex &index) const
{
  if( !index.isValid() )
    return QModelIndex();

  QObject *indexObject = static_cast<QObject*>( index.internalPointer() );
  QObject *parentObject = indexObject->parent();
  
  if( parentObject == m_root )
    return QModelIndex();

  QObject *grandParentObject = parentObject->parent();
  
  return createIndex( grandParentObject->children().indexOf( parentObject ), 0, parentObject );
}
