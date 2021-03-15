#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H
#include "node_visitor.h"
#include "string"
#include <map>
class Node;

class FindVisitor: public NodeVisitor
{
    public:
        FindVisitor(std::string name);
        void visitFolder(Folder * folder);
        void visitFile(File * file);
        void stringFolder(std::string _folderName);
        std::string findResult();

    private:
        bool _isFirst = true;
        std::map<std::string,Node*> _recordChild;
        std::string _folderName;
        std::string _name;
        std::string _result = "";
};


#endif
