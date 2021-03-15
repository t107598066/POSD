#include "find_node_by_pathname_visitor.h"
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include <vector>
#include <iostream>
FindNodeByPathnameVisitor::FindNodeByPathnameVisitor(std::vector<std::string>* pathnames):_pathnames(pathnames),_node(nullptr),_nodePath("")
{
  // _nodePath = ".";
  // std::vector<std::string>::iterator it;
  // for(it = _pathnames->begin();it != _pathnames->end();it++)
  // {
  //   _nodePath = _nodePath + "/" + (*it);
  // }
  _it = _pathnames->begin();
}

void FindNodeByPathnameVisitor::visitFile(File * file)
{
//   if(_pathnames->size() == 1)
//   {
//     _node = file;
//   }
//
//   if(file->path() + file->name() == _nodePath)//判斷fileInFolder
//   {
//     _node = file;
//   }

  if(_pathnames->size() > 0)
  {
    if(*_it == file->name())
    {
      _node = file;
    }
  }
}

void FindNodeByPathnameVisitor::visitFolder(Folder * folder)
{
  // NodeIterator * it = folder->createIterator();
  // for (it->first(); !it->isDone(); it->next())
  // {
  //   it->currentItem()->accept(this);
  // }
  // if(folder->path() + folder->name() == _nodePath)
  // {
  //   std::cout << _nodePath << std::endl;
  //   std::cout << folder->path() + folder->name() << std::endl;
  //   _node = folder;
  // }
  if(_pathnames->size() > 0)
  {
    if(*_it == folder->name())
    {
      if(_it == _pathnames->end()-1)//判斷folder是最後一個
      {
        _node = folder;
      }
      else
      {
        _it++;
        NodeIterator * it2 = folder->createIterator();
        for (it2->first(); !it2->isDone(); it2->next())
        {
          it2->currentItem()->accept(this);
        }
      }
    }
  }
}

void FindNodeByPathnameVisitor::visitLink(Link * link)
{
  // std::vector<std::string>::iterator it;
  // for (it = _pathnames->begin();it != _pathnames->end();it++)
  // {
  //   if(*it == link->name())
  //   {
  //     _node = link;
  //   }
  // }
  if(_pathnames->size() > 0)
  {
    if(*_it == link->name())
    {
      _node = link;
    }
  }
}

Node * FindNodeByPathnameVisitor::getNode() const
{
  return _node;
}
