#ifndef FOLDER_H
#define FOLDER_H
#include <iostream>
#include <vector>
#include "node.h"

class Folder:public Node{
public:
  Folder(const char* path):Node(path)
  {

  }

  void add(Node *node)
  {
    _children.push_back(node);
  }

  int infoContent() const
  {
    int sum = 0;
    for(int i = 0; i < _children.size(); i++)
    {
      sum += _children[i]->infoContent();
    }
    return sum;
  }

  int numberOfChildren() const
  {
    return _children.size();
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
    std::cout << outputResult(results) << std::endl;
    return outputResult(results);


}

  std::string outputResult(std::vector<std::string> results) const
  {
    std::string content = "";
    for(std::string str : results)
    {
      content += str;
      if(str != results.back())
      {
        content += "\n";
      }
    }
    return content;
  }

  void findNodeIterative(std::string nodeName, std::vector<Node*>& result) const
  {
    for(Node *node : _children)
    {
      if(node->name() == nodeName)
      {
        result.push_back(node);
      }
      node->findNodeIterative(nodeName, result);
    }
  }

private:
  std::vector<Node *> _children;
};

#endif
