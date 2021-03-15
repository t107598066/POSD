#ifndef INFO_CONTENT_VISITOR_H
#define INFO_CONTENT_VISITOR_H
#include "node_visitor.h"

class InfoContentVisitor: public NodeVisitor
{
public:
  InfoContentVisitor();

  void visitFile(File * file);
  void visitFolder(Folder * folder);
  int getContentSize();

private:
  int _size;
};

#endif
