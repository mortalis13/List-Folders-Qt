#include "treemodel.h"

TreeModel::TreeModel(DirNode *root, QObject *parent) : QAbstractItemModel(parent){
  m_root = root;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const{
  if( !index.isValid() )
    return QVariant();

  if( role == Qt::DisplayRole ){
      return static_cast<TreeNode*>( index.internalPointer() )->text;
  }
  
  return QVariant();
}

int TreeModel::rowCount(const QModelIndex &parent) const{
  DirNode *parentObject;

  if( !parent.isValid() )
    parentObject = m_root;
  else{
    TreeNode* temp = static_cast<TreeNode*>( parent.internalPointer() );
    parentObject = dynamic_cast<DirNode*>(temp);
    if(!parentObject)
      return 0;
  }

  return parentObject->treeChildren->size();
}

int TreeModel::columnCount(const QModelIndex &parent) const{
  return 1;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const{
  DirNode *parentObject;

  if( !parent.isValid() )
    parentObject = m_root;
  else{
    TreeNode* temp = static_cast<TreeNode*>( parent.internalPointer() );
    parentObject = dynamic_cast<DirNode*>(temp);
    if(!parentObject)
      parentObject = m_root;
  }

  if( row < parentObject->treeChildren->size() ){
    TreeNode* child=parentObject->treeChildren->at(row);
    return createIndex( row, column, child );
  }
  else
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const{
  if( !index.isValid() )
    return QModelIndex();
 
  TreeNode *indexObject = static_cast<TreeNode*>( index.internalPointer() );
  TreeNode *parentObject = indexObject->m_parent;

  if( parentObject == m_root )
    return QModelIndex();
  
  DirNode *grandParentObject = dynamic_cast<DirNode*>( parentObject->m_parent );
  if(!grandParentObject)
    return QModelIndex();
    
  return createIndex( grandParentObject->treeChildren->indexOf( parentObject ), 0, parentObject );
}
