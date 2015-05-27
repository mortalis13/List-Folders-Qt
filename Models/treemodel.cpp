#include "treemodel.h"

#include <QIcon>

#include "Models/modelfunctions.h"

TreeModel::TreeModel(DirNode *root, QObject *parent) : QAbstractItemModel(parent){
  m_root = root;
  iconsPath="lib/icons/";
}

// ------------------------------------------- overridden -------------------------------------------

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*
 * Returns text to display and icons for tree nodes
 */
QVariant TreeModel::data(const QModelIndex &index, int role) const{
  if( !index.isValid() )
    return QVariant();

  if(TreeNode* item=static_cast<TreeNode*>( index.internalPointer() )){
    if( role == Qt::DisplayRole ){                                         // text
      return item->text;
    }

    if (role == Qt::DecorationRole){                                       // icon
      QString itemIconPath=item->icon;
      QString iconName=ModelFunctions::extractIconName(itemIconPath);       // get the icon name ('music' from 'lib/images/music.png')

      QIcon icon(iconsPath+iconName);
      return icon;
    }
  }
  
  return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const{
  DirNode *parentObject;

  if( !parent.isValid() )
    parentObject = m_root;
  else{
    TreeNode* temp = static_cast<TreeNode*>( parent.internalPointer() );
    parentObject = dynamic_cast<DirNode*>(temp);
    if(!parentObject)                                                           // if not DirNode (FileNode doesn't have 'treeChildren')
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

int TreeModel::rowCount(const QModelIndex &parent) const{
  DirNode *parentObject;

  if( !parent.isValid() )
    parentObject = m_root;
  else{
    TreeNode* temp = static_cast<TreeNode*>( parent.internalPointer() );
    parentObject = dynamic_cast<DirNode*>(temp);                              // dynamic cast to distinguish DirNode from FileNode
    if(!parentObject)
      return 0;
  }

  return parentObject->treeChildren->size();
}

int TreeModel::columnCount(const QModelIndex &parent) const{
  return 1;
}

// ------------------------------------------- custom -------------------------------------------

DirNode* TreeModel::getRoot(){
  return m_root;
}

void TreeModel::prepareIcons(){
//  icons.append(QIcon(iconsPath+"directory.png"));
}
