#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H

class Folder;
class File;

class NodeVisitor
{
  public:
      virtual void visitFolder(Folder * folder) = 0;
      virtual void visitFile(File * file) = 0;
};

#endif
