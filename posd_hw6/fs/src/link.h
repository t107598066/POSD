#ifndef LINK_H
#define LINK_H
#include "node.h"

class Link : public Node{
public:
  Link(const char * path, Node * node = nullptr) : Node(path)
  {
    if(!S_ISLNK(_st.st_mode))
    {
      throw std::string("Do not indicate the Link path.");
    }
    this->addLink(node);
  }

  void accept(Visitor * v)
  {
    v->visitLink(this);
  }

  void addLink(Node * node)
  {
    _source = node;
  }

  Node * getSource() {
    return _source;
  }

private:
  Node * _source;
};

#endif
