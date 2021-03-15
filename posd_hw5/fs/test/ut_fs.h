#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/info_content_visitor.h"
#include "../src/node_iterator.h"

TEST (MiscTest, lstatOnFolder)
{
  const char * path = "./test_data";
  struct stat st;
  ASSERT_EQ(0, lstat(path, &st));
  ASSERT_EQ(512, st.st_size);
  ASSERT_EQ(true, S_ISDIR(st.st_mode));
  ASSERT_EQ(false, S_ISREG(st.st_mode));
  ASSERT_EQ(false, S_ISLNK(st.st_mode));
}

TEST (FileSystemTest, Size)
{
  Node * test_data = new Folder ("./test_data");
  ASSERT_EQ(512,test_data->size());
  Node * folder = new Folder("./test_data/folder");
  ASSERT_EQ(512, folder->size());
  Node * hello_cpp = new File("./test_data/hello.cpp");
  ASSERT_EQ(83, hello_cpp->size());
  Node * a_out = new File("./test_data/folder/a.out");
  ASSERT_EQ(8432, a_out->size());
  test_data->add(folder);
  test_data->add(hello_cpp);
  ASSERT_EQ(2,test_data->numberOfChildren());
}

TEST (FileSystemTest, Visitor)
{
  File * a_out = new File("./test_data/folder/a.out");
  InfoContentVisitor * icv = new InfoContentVisitor();
  a_out->accept(icv);
  ASSERT_EQ(8432, icv->getContentSize());
  delete icv;
  // icv = new InfoContentVisitor();
  InfoContentVisitor * icv2 = new InfoContentVisitor();
  Node * folder = new Folder("./test_data/folder");
  folder->add(a_out);
  folder->accept(icv2);
  ASSERT_EQ(8432, icv2->getContentSize());

  InfoContentVisitor * icv3 = new InfoContentVisitor();
  Node * test_data = new Folder("./test_data");
  Node * hello_cpp = new File("./test_data/hello.cpp");
  test_data->add(folder);
  test_data->add(hello_cpp);
  test_data->accept(icv3);
  ASSERT_EQ(8515,icv3->getContentSize());

}
TEST(FileSystemTest,NodeIterator){
  Node * folder = new Folder("./test_data/folder");
  Node * test_data = new Folder("./test_data");
  Node * hello_cpp = new File("./test_data/hello.cpp");
  Node * a_out = new File("./test_data/folder/a.out");
  test_data->add(folder);
  test_data->add(hello_cpp);
  folder->add(a_out);
  NodeIterator * it = test_data->createIterator();
  it->first();
  ASSERT_EQ(512, it->currentItem()->size());
  it->next();
  ASSERT_EQ(83, it->currentItem()->size());
  it->next();
  ASSERT_TRUE(it->isDone());
  ASSERT_ANY_THROW(it->currentItem());
  ASSERT_ANY_THROW(it->next());
}

#endif
