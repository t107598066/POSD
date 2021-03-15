#include "find_link_visitor.h"
#include "folder.h"
#include "file.h"
#include "link.h"
#include <iostream>
FindLinkVisitor::FindLinkVisitor(): _links(std::vector<Node*>{})
{

}

void FindLinkVisitor::visitFolder(Folder * folder)
{
  std::cout << folder->name() << '\n';
  NodeIterator * it = folder->createIterator();
  for (it->first(); !it->isDone(); it->next())
  {
    it->currentItem()->accept(this);
  }
}

void FindLinkVisitor::visitFile(File * file)
{

}

void FindLinkVisitor::visitLink(Link * link)
{
  std::cout << link->path() << '\n';
  std::cout << link->name() << '\n';
  // std::cout << link->getSource()->name() << '\n';
  _links.push_back(link);
}

std::vector<Node*> FindLinkVisitor::getLinks()
{
  return _links;
}
