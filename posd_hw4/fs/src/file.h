#ifndef FILE_H
#define FILE_H

#include "node.h"

class File: public Node{
public:
  File(const char * path): Node(path)
  {

  }

  std::string find(std::string nodeName) const
  {
    if(Node::name() == nodeName)
    {
      return Node::name();
    }
    else
    {
      return "";
    }
  }

};

#endif
