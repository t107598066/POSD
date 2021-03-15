#include "find_visitor.h"
#include "folder.h"
#include "file.h"

FindVisitor::FindVisitor(std::string name): _name(name),_result("")
{

}

void FindVisitor::visitFolder(Folder * folder)
{
  _result = folder->find(_name);
}

void FindVisitor::visitFile(File * file)
{
  _result = file->find(_name);
}

std::string FindVisitor::findResult()
{
  return _result;
}
