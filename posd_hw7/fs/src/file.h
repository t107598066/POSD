#ifndef FILE_H
#define FILE_H

#include "node.h"
#include "node_visitor.h"

class File: public Node{
public:
  File(const char * path): Node(path)
  {
    if (!S_ISREG(_st.st_mode))
    {
      throw std::string("Do not indicate the file path.");
    }
  }

  void accept(Visitor * v)
  {
    v->visitFile(this);
  }
};

#endif
