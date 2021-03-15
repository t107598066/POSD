#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H
#include "node_visitor.h"
#include "string"
class Folder;
class File;

class FindVisitor: public NodeVisitor
{
    public:
        FindVisitor(std::string name);
        void visitFolder(Folder * folder);
        void visitFile(File * file);
        std::string findResult();//return relative path which are found by name.

    private:
        std::string _name;
        std::string _result;
};


#endif
