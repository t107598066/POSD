#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include "../src/folder.h"
#include "../src/file.h"

TEST (, FileSearchItsSelf)
{
  Node * a_out = new File("./test_data/folder/a.out");
  ASSERT_EQ("a.out",a_out->find("a.out"));
}
TEST (, FileSearchNotItsSelf)
{
  Node * a_out = new File("./test_data/folder/a.out");
  ASSERT_EQ("",a_out->find("b.out"));
}
TEST (, FolderSearchItsSelf)
{
  Node * folder = new Folder("./test_data/folder");
  ASSERT_EQ("",folder->find("folder"));
}
TEST (, FolderSearchNotItsSelf)
{
  Node * folder = new Folder("./test_data/folder");
  ASSERT_EQ("",folder->find("test_data"));
}

TEST (, SearchFileInFolder)
{
  Node * folder = new Folder("./test_data/folder");
  Node * a_out = new File("./test_data/folder/a.out");
  folder->add(a_out);
  ASSERT_EQ("./a.out",folder->find("a.out"));
}

TEST (, SearchFolderInFolder)
{
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  test_data->add(folder);
  ASSERT_EQ("./folder",test_data->find("folder"));
}

TEST(, SearchTAFileInFolder) {
    Node *test_data = new Folder("./test_data");
    Node *folder = new Folder("./test_data/folder");
    Node *ta_folder = new Folder("./test_data/folder/ta_folder");
    Node *ta_out = new File("./test_data/folder/ta_folder/ta.out");
    ta_folder->add(ta_out);
    folder->add(ta_folder);
    test_data->add(folder);
    ASSERT_EQ("./ta_folder/ta.out", folder->find("ta.out"));
}


#endif
