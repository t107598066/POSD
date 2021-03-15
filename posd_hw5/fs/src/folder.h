#include <map>
#include <vector>
#include <string>
#include "node.h"
#include "info_content_visitor.h"
#include "node_iterator.h"

class Folder:public Node{
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

  }

  void add(Node *node)
  {
    _children.insert(std::pair<std::string,Node*>(node->name(),node));
  }

  int numberOfChildren() const
  {
    return _children.size();
  }

  void accept(InfoContentVisitor * icv)
  {
    icv->visitFolder(this);
  }

  NodeIterator * createIterator()
  {
    return new FolderIterator(this);
  }

  std::string find(std::string nodeName) const
  {
    std::vector<Node*> resultNode;
    std::vector<std::string> results;
    findNodeIterative(nodeName, resultNode);
    std::string folderToFind = Node::name();
    for(Node *node : resultNode)
    {
      int currentFindPos = node->path().find("/" + folderToFind);//把資料夾弄出位置
      if(currentFindPos != std::string::npos)
      {
        results.push_back("." + node->path().substr(currentFindPos + folderToFind.size() + 1) + node->name());
        //刪掉 folderToFind 位置 加上 resultNode 位置
      }
    }
    return outputResult(results);
}

  std::string outputResult(std::vector<std::string> results) const
  {
    std::string content = "";
    std::vector<std::string>::const_iterator it;
    for(it = results.begin();it != results.end();it++)
    {
      content += (*it);
      if((*it) != results.back())
      {
        content += "\n";
      }
    }
    return content;
  }

  void findNodeIterative(std::string nodeName, std::vector<Node*>& result) const
  {
    std::map<std::string, Node*>::const_iterator it;
    for(it = _children.begin(); it != _children.end(); it++)
    {
      if(it->second->name() == nodeName)
      {
        result.push_back(it->second);
      }
      it->second->findNodeIterative(nodeName, result);
    }
  }

private:
  std::map<std::string,Node*> _children;
};
