#ifndef FOLDER_H
#define FOLDER_H

#include <map>
#include <string>
#include "node.h"
#include "node_visitor.h"
#include "node_iterator.h"
#include <iostream>

class Folder: public Node
{
public:
  class FolderIterator : public NodeIterator
  {
  public:

    FolderIterator(Folder * f): _folder(f)
    {

    }

    void first()
    {
      _it = _folder->_children.begin();
    }

    Node* currentItem()
    {
      if (isDone())
      {
        throw std::string("no current item");
      }
      return _it->second;
    }

    void next()
    {
      if (isDone())
      {
        throw std::string("moving past the end");
      }
      _it++;
    }

    bool isDone()
    {
      return _it == _folder->_children.end();
    }

  private:
    Folder * _folder;
    std::map<std::string,Node*>::iterator _it;
  };

  Folder(const char* path):Node(path)
  {
    if (!S_ISDIR(this->_st.st_mode))
    {
     throw std::string("Do not indicate the Folder path.");
    }
  }

  void add(Node *node)
  {
    node->setParent(this);
    _children.insert(std::pair<std::string,Node*>(node->path() + node->name(),node));
  }

  int numberOfChildren() const
  {
    return _children.size();
  }

  void accept(Visitor * v)
  {
    v->visitFolder(this);
  }

  NodeIterator * createIterator()
  {
    return new FolderIterator(this);
  }

  std::string find(std::string nodeName)
  {
    std::map<std::string,Node*> resultNode;
    std::map<std::string,std::string> results;
    findNodeIterative(nodeName, resultNode);
    std::string folderToFind = Node::name();
    std::map<std::string, Node*>::iterator it;
    for(it = resultNode.begin();it != resultNode.end();it++)
    {
      int currentFindPos = it->first.find("/" + folderToFind);//把資料夾弄出位置
      if(currentFindPos != std::string::npos)
      {
        results.insert(std::pair<std::string,std::string>("." + it->first.substr(currentFindPos + folderToFind.size() + 1) + it->second->name(),"." + it->first.substr(currentFindPos + folderToFind.size() + 1) + it->second->name()));
        //刪掉 folderToFind 位置 加上 resultNode 位置
      }
    }
    std::map<std::string, std::string>::iterator it_results;
    std::string content = "";
    for(it_results = results.begin(); it_results != results.end(); it_results++ )
    {
      content += it_results->second;
      if(it_results->second != results.rbegin()->second)
      {
        content += "\n";
      }
    }
    return content;
  }

  void findNodeIterative(std::string nodeName, std::map<std::string,Node*>& result) const
  {
    std::map<std::string,Node*>::const_iterator it;
    for(it = _children.begin(); it != _children.end(); it++)
    {
      if(it->second->name() == nodeName)
      {
        result.insert(std::pair<std::string,Node*>(it->second->path(),it->second));
      }
      it->second->findNodeIterative(nodeName, result);
    }
  }

private:
  std::map<std::string,Node*> _children;
};

#endif
