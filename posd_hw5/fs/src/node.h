#ifndef NODE_H
#define NODE_H
#include <sys/stat.h>
#include <string>
#include <vector>
#include "node_iterator.h"

class InfoContentVisitor;

class Node
{
public:
  Node(const char * path): _path(path)
  {
    lstat(_path, &_st);
  }

  int size() const
  {
    return _st.st_size;
  }

  virtual void accept(InfoContentVisitor * icv) = 0;

  virtual void add(Node *node)
  {
    throw std::string("unable to add");
  }

  virtual int numberOfChildren() const
  {
    throw std::string("number of children: not applicable");
  }

  virtual NodeIterator* createIterator()
  {
    return nullptr;
  }

  std::string name() const
  {
    std::string name;
    std::string path = _path;
    int finalSlash = path.rfind('/');
    return path.substr(finalSlash+1);
    //name : ./a/b/c.out  -> c.out
  }

  std::string path() const
  {
    std::string path = std::string(_path);
    int finalSlash = path.rfind("/");
    return path.substr(0, finalSlash+1);
    // path : ./a/b/c.out  -> ./a/b/
  }

  virtual std::string find(std::string nodeName) const
  {
    throw std::string("Can't find the target.");
  }

  virtual void findNodeIterative(std::string nodeName, std::vector<Node*>& result) const
  {

  }

private:
  const char * _path;
  struct stat _st;
};

#endif
