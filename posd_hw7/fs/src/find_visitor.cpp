#include "find_visitor.h"
#include "node.h"
#include "folder.h"
#include "file.h"
#include "link.h"
#include <iostream>

FindVisitor::FindVisitor(std::string name): _name(name)
{

}

void FindVisitor::visitFolder(Folder * folder)
{
  if(_isFirst)
  {
    _recordChild.clear();
    _folderName = folder->name();
  }
  NodeIterator * it = folder->createIterator();
  for (it->first(); !it->isDone(); it->next())
  {
    if(it->currentItem()->name() == _name)
    {
      _recordChild.insert(std::pair<std::string,Node*>(it->currentItem()->path(),it->currentItem()));
    }
    _isFirst = false;
    it->currentItem()->accept(this);

  }
  stringFolder(_folderName);
  // std::map<std::string,Node*>::const_iterator itt;
  // for(itt = _recordChild.begin(); itt != _recordChild.end(); itt++)
  // {
  //   std::cout << itt->first << std::endl;;
  // }

}

void FindVisitor::stringFolder(std::string _folderName)
{
  std::map<std::string,Node*> resultNode;
  std::map<std::string,std::string> results;

  resultNode = _recordChild;
  std::string folderToFind = _folderName;
  std::map<std::string, Node*>::iterator it;
  for(it = resultNode.begin();it != resultNode.end();it++)
  {
    int currentFindPos = it->first.find("/" + folderToFind);//把資料夾弄出位置
    if(currentFindPos != std::string::npos)
    {
      results.insert(std::pair<std::string,std::string>("." + it->first.substr(currentFindPos + folderToFind.size() + 1) + it->second->name(),"." + it->first.substr(currentFindPos + folderToFind.size() + 1) + it->second->name()));
      //刪掉 folderToFind 位置 加上 resultNode 位置
    }
  }
  std::map<std::string, std::string>::iterator it_results;
  std::string content = "";
  for(it_results = results.begin(); it_results != results.end(); it_results++ )
  {
    content += it_results->second;
    if(it_results->second != results.rbegin()->second)
    {
      content += "\n";
    }
  }
  _result =  content;
}

void FindVisitor::visitFile(File * file)
{
  if(file->name() == _name)
  {
    _result = file->name();
  }
  else
  {
    _result = "";
  }
}

void FindVisitor::visitLink(Link * link)
{
 link->getSource()->accept(this);
}

std::string FindVisitor::findResult()
{
  _isFirst = true;
  return _result;
}
