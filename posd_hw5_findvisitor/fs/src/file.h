#ifndef FILE_H
#define FILE_H

#include "node.h"
#include "node_visitor.h"
#include "null_iterator.h"

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

  NodeIterator * createIterator()
  {
    return new NullIterator();
  }

  void accept(NodeVisitor * nv)
  {
    nv->visitFile(this);
  }
};

#endif
