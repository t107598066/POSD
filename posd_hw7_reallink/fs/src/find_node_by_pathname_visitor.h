#ifndef FIND_NODE_BY_PATHNAME_VISITOR_H
#define FIND_NODE_BY_PATHNAME_VISITOR_H
#include "node_visitor.h"
#include <vector>
#include "string"
#include "node.h"

class FindNodeByPathnameVisitor : public Visitor
{
public:
    FindNodeByPathnameVisitor(std::vector<std::string>* pathnames);
    void visitFolder(Folder * folder);
    void visitFile(File * file);
    void visitLink(Link * link);
    Node * getNode() const; //return the Node object if the path indicate the node in the file system, and if not, return nullptr.

private:
    std::vector<std::string>* _pathnames;
    Node * _node;
    std::string _nodePath;
    std::vector<std::string>::iterator _it;

};
#endif
