#ifndef FIND_LINK_VISITOR_H
#define FIND_LINK_VISITOR_H
#include "node_visitor.h"
#include "string"
#include <vector>
#include "node.h"

class FindLinkVisitor : public Visitor
{
public:
    FindLinkVisitor();
    void visitFolder(Folder * folder);
    void visitFile(File * file);
    void visitLink(Link * link);
    std::vector<Node*> getLinks();

private:
    std::vector<Node*> _links;
};

#endif
