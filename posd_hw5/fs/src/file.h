#ifndef FILE_H
#define FILE_H

#include "node.h"
#include "info_content_visitor.h"

class File: public Node{
public:
  File(const char * path): Node(path)
  {

  }

  void accept(InfoContentVisitor * icv)
  {
    icv->visitFile(this);
  }
};

#endif
