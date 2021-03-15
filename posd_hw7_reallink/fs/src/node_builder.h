#ifndef NODE_BUILDER_H
#define NODE_BUILDER_H
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

class NodeBuilder
{
public:
  NodeBuilder()
  {

  }

  void build (const char * path)
  {
    struct stat st;
    if (lstat(path, &st) == 0)
    {
      if (S_ISREG(st.st_mode))
      {
        _root = new File(path);
      }
      else if (S_ISLNK(st.st_mode))
      {
        // std::string _getLink = getLink(path);
        // std::cout << "_getLink: " << _getLink << std::endl;
        // std::cout << "_rootLinkParent: " << _rootLinkParent->name() << std::endl;
        //
        const char * real_path = realpath(path, NULL);
        // std::string _path = std::string(path);
        NodeBuilder nb;
        nb.build(real_path);
        std::cout << "path: " << _root->name() << std::endl;
        std::cout << "path: " << real_path << std::endl;

        _root = new Link(path,nb.getRoot());
        _rootNode = _root;
        std::cout << "path: " << path << std::endl;
        std::cout << "_root->name(): " <<_root->name() << std::endl;
      }
      else if (S_ISDIR(st.st_mode))
      {
        // _root = new Folder(path);
        // DIR * dir = opendir(path);
        // if (dir == nullptr)
        //   throw std::string("open folder error");
        // struct dirent * entry = nullptr;
        //
        // while((entry = readdir(dir)) != nullptr)
        // {
        //   if (std::string(entry->d_name) != "." && std::string(entry->d_name) != "..")
        //   {
        //     NodeBuilder nb;
        //     std::string tempString = (std::string(path) + "/" + entry->d_name);
        //     const char * pathName = tempString.c_str();
        //     nb.build(pathName);
        //     _root->add(nb.getRoot());
        //   }
        // }

        char *real_path = realpath(path, NULL);
        _root = new Folder(real_path);
        DIR * dir = opendir(real_path);
        if (dir == nullptr)
          throw std::string("open folder error");
        struct dirent * entry = nullptr;
        while((entry = readdir(dir)) != nullptr)
        {
          if (std::string(entry->d_name) != "." && std::string(entry->d_name) != "..")
          {
            std::string tempString = (std::string(real_path) + "/" + entry->d_name);
            const char * pathChild = tempString.c_str();
            NodeBuilder nb ;
            nb.build(pathChild);
            _root->add(nb.getRoot());
            if(_rootNode != nullptr)
            {
              std::cout << "dwwwww" << _rootNode->name() << std::endl;
            }
            std::cout << "dasdasdasd" << nb.getRoot() << std::endl;
            std::cout << path << std::endl;
            std::cout << pathChild << std::endl;
            std::cout << _root->name() << std::endl;
            std::cout << "-------------------------------------------------------" << std::endl;
          }
        }
      }
    }
  }

  std::string getLink(const char * path)
  {
    char buff[1024];
    ssize_t len = ::readlink(path,buff,sizeof(buff)-1);
    if (len != -1) {
      buff[len] = '\0';
      return std::string(buff);
    }
  }

  Node * getRoot()
  {
    return _root;
  }


private:
  Node * _rootNode = nullptr;
  Node * _root;
};

#endif
