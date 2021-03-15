#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/info_content_visitor.h"
#include "../src/find_visitor.h"
#include "../src/node_iterator.h"

// TEST (MiscTest, lstatOnFolder)
// {
//   const char * path = "./test_data";
//   struct stat st;
//   ASSERT_EQ(0, lstat(path, &st));
//   ASSERT_EQ(4096, st.st_size);
//   ASSERT_EQ(true, S_ISDIR(st.st_mode));
//   ASSERT_EQ(false, S_ISREG(st.st_mode));
//   ASSERT_EQ(false, S_ISLNK(st.st_mode));
// }
//
// TEST (FileSystemTest, Size)
// {
//   Node * test_data = new Folder ("./test_data");
//   ASSERT_EQ(4096,test_data->size());
//   Node * folder = new Folder("./test_data/folder");
//   ASSERT_EQ(4096, folder->size());
//   Node * hello_cpp = new File("./test_data/hello.cpp");
//   ASSERT_EQ(83, hello_cpp->size());
//   Node * a_out = new File("./test_data/folder/a.out");
//   ASSERT_EQ(8432, a_out->size());
//   test_data->add(folder);
//   test_data->add(hello_cpp);
//   ASSERT_EQ(2,test_data->numberOfChildren());
// }
//
// TEST (FileSystemTest, Visitor)
// {
//   File * a_out = new File("./test_data/folder/a.out");
//   InfoContentVisitor * icv = new InfoContentVisitor();
//   a_out->accept(icv);
//   ASSERT_EQ(8432, icv->getContentSize());
//   delete icv;
//   // icv = new InfoContentVisitor();
//   InfoContentVisitor * icv2 = new InfoContentVisitor();
//   Node * folder = new Folder("./test_data/folder");
//   folder->add(a_out);
//   folder->accept(icv2);
//   ASSERT_EQ(8432, icv2->getContentSize());
//
//   InfoContentVisitor * icv3 = new InfoContentVisitor();
//   Node * test_data = new Folder("./test_data");
//   Node * hello_cpp = new File("./test_data/hello.cpp");
//   test_data->add(folder);
//   test_data->add(hello_cpp);
//   test_data->accept(icv3);
//   ASSERT_EQ(8515,icv3->getContentSize());
//
// }
// TEST(FileSystemTest,NodeIterator){
//   Node * folder = new Folder("./test_data/folder");
//   Node * test_data = new Folder("./test_data");
//   Node * hello_cpp = new File("./test_data/hello.cpp");
//   Node * a_out = new File("./test_data/folder/a.out");
//   test_data->add(folder);
//   test_data->add(hello_cpp);
//   folder->add(a_out);
//   NodeIterator * it = test_data->createIterator();
//   it->first();
//   ASSERT_EQ(4096, it->currentItem()->size());
//   it->next();
//   ASSERT_EQ(83, it->currentItem()->size());
//   it->next();
//   ASSERT_TRUE(it->isDone());
//   ASSERT_ANY_THROW(it->currentItem());
//   ASSERT_ANY_THROW(it->next());
// }
//
// TEST(, FileSearchItsSelf) {
//     File * a_out = new File("./test_data/folder/a.out");
//     FindVisitor * fcv = new FindVisitor("a.out");
//     a_out->accept(fcv);
//     ASSERT_EQ("a.out", fcv->findResult());
// }
//
// TEST(, FileSearchNotItsSelf) {
//     File * a_out = new File("./test_data/folder/a.out");
//     FindVisitor * fcv = new FindVisitor("b.out");
//     a_out->accept(fcv);
//     ASSERT_EQ("", fcv->findResult());
// }
//
// TEST(, FolderSearchItsSelf) {
//     Folder * folder = new Folder("./test_data/folder");
//     FindVisitor * fcv = new FindVisitor("folder");
//     folder->accept(fcv);
//     ASSERT_EQ("", fcv->findResult());
// }
// //
// TEST(, FolderSearchNotItsSelf) {
//     Folder * folder = new Folder("./test_data/folder");
//     FindVisitor * fcv = new FindVisitor("test_data");
//     folder->accept(fcv);
//     ASSERT_EQ("", fcv->findResult());
// }
//
// TEST(, SearchFileInFolder) {
//     Folder * folder = new Folder("./test_data/folder");
//     File * a_out = new File("./test_data/folder/a.out");
//     folder->add(a_out);
//     FindVisitor * fcv = new FindVisitor("a.out");
//     folder->accept(fcv);
//     ASSERT_EQ("./a.out", fcv->findResult());
// }
//
// TEST(, SearchFolderInFolder) {
//     Folder * test_data = new Folder("./test_data");
//     Folder * folder = new Folder("./test_data/folder");
//     test_data->add(folder);
//     FindVisitor * fcv = new FindVisitor("folder");
//     test_data->accept(fcv);
//     ASSERT_EQ("./folder", fcv->findResult());
// }

TEST(, SearchTAFileInFolder) {
    Folder * folder = new Folder("./folder");
    Folder * folder2 = new Folder("./folder/folder");
    Folder * ta_folder = new Folder("./folder/folder/ta_folder");
    Folder * ta_folder2 = new Folder("./folder/folder/ta_folder/ta_folder");
    File * a_out = new File("./folder/folder/ta_folder/ta_folder/a.out");
    folder->add(folder2);
    folder2->add(ta_folder);
    ta_folder->add(ta_folder2);
    ta_folder2->add(a_out);
    FindVisitor * fcv3 = new FindVisitor("a.out");
    folder->accept(fcv3);
    ASSERT_EQ("./folder/ta_folder/ta_folder/a.out", fcv3->findResult());
    ASSERT_EQ("./folder/ta_folder/ta_folder/a.out", folder->find("a.out"));

    FindVisitor * fcv2 = new FindVisitor("folder");
    folder->accept(fcv2);
    ASSERT_EQ("./folder", fcv2->findResult());
    ASSERT_EQ("./folder", folder->find("folder"));
    FindVisitor * fcv = new FindVisitor("ta_folder");
    folder->accept(fcv);
    ASSERT_EQ("./folder/ta_folder\n./folder/ta_folder/ta_folder", fcv->findResult());
    ASSERT_EQ("./folder/ta_folder\n./folder/ta_folder/ta_folder", folder->find("ta_folder"));

}

#endif
