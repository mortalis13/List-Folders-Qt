
#include <QMetaObject>

#include "testtreemodel.h"

TestTreeModel::TestTreeModel( Test *root, QObject *parent ) : QAbstractItemModel( parent ){
  m_root = root;
}

Qt::ItemFlags TestTreeModel::flags(const QModelIndex &index) const{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TestTreeModel::data( const QModelIndex &index, int role) const{
  if( !index.isValid() )
    return QVariant();

//  qDebug() << "role: " << role;

  if( role == Qt::DisplayRole ){
    switch( index.column() ){
    case 0:
//      return static_cast<Test*>( index.internalPointer() )->text;
      return "text";
    default:
      break;
    }
  }

  return QVariant();
}

int TestTreeModel::rowCount(const QModelIndex &parent ) const{
  Test *parentObject;
  
  if( !parent.isValid() )
    parentObject = m_root;
  else
    parentObject = static_cast<Test*>( parent.internalPointer() );

  int rows=parentObject->children->size();
//  qDebug() << "rows: " << rows;

  return rows;
}

int TestTreeModel::columnCount(const QModelIndex &parent ) const{
  return 1;
}

QModelIndex TestTreeModel::index(int row, int column, const QModelIndex &parent ) const{
  Test *parentObject;
  
  if( !parent.isValid() ){
    parentObject = m_root;
  }
  else{
    parentObject = static_cast<Test*>( parent.internalPointer() );
//    qDebug() << "text: " << parentObject->text;
  }

  if( row < parentObject->children->size() ){
//    qDebug() << "  index(), row < :: " << row << ", " << column;
    return createIndex( row, column, parentObject->children->at( row ) );
  }
  else{
    qDebug() << "  index(), !row < :: " << row << ", " << column;
    return QModelIndex();
  }
}

QModelIndex TestTreeModel::parent(const QModelIndex &index) const{
  if( !index.isValid() )
    return QModelIndex();

  Test *indexObject = static_cast<Test*>( index.internalPointer() );
  Test *parentObject = indexObject->parent;
//  qDebug() << "parent(), text: " << parentObject->text;
  
  if( parentObject == m_root )
    return QModelIndex();

  qDebug("grandParentObject");

  Test *grandParentObject = parentObject->parent;
  
  return createIndex( grandParentObject->children->indexOf( parentObject ), 0, parentObject );
}
