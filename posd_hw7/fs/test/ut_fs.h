#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/link.h"
#include "../src/info_content_visitor.h"
#include "../src/find_link_visitor.h"
#include "../src/find_node_by_pathname_visitor.h"
#include "../src/node_iterator.h"
#include "../src/node_builder.h"
#include <memory>
#include <iostream>

TEST(MiscTest, lstatOnFolder) {
    const char *path = "./test_data";
    struct stat st;
    ASSERT_EQ(0, lstat(path, &st));
    ASSERT_EQ(4096, st.st_size);
    ASSERT_EQ(true, S_ISDIR(st.st_mode));
    ASSERT_EQ(false, S_ISREG(st.st_mode));
    ASSERT_EQ(false, S_ISLNK(st.st_mode));
}

class FileSystemTest : public ::testing::Test {
  protected:
    void SetUp() override {
        test_data = new Folder("./test_data");
        folder = new Folder("./test_data/folder");
        hello_cpp = new File("./test_data/hello.cpp");
        a_out = new File("./test_data/folder/a.out");
        hello = new Link("./test_data/hello", a_out);
        folder->add(a_out);
        test_data->add(folder);
        test_data->add(hello);
        test_data->add(hello_cpp);
    }

    void TearDown() override {
        delete a_out;
        delete hello_cpp;
        delete hello;
        delete folder;
        delete test_data;
    }

    Node *test_data;
    Node *folder;
    Node *hello_cpp;
    Node *a_out;
    Node *hello;
};

TEST_F (FileSystemTest, GetParent) {
    Node* test_data = new Folder("./test_data");
    Node* folder = new Folder("./test_data/folder");
    test_data->add(folder);
    ASSERT_EQ(test_data, folder->getParent());
}

TEST_F (FileSystemTest, File) {
    Node* hello_cpp = new File("./test_data/hello.cpp");
    std::vector<std::string>* names = new std::vector<std::string>{std::string("hello.cpp")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    hello_cpp->accept(fv);
    ASSERT_EQ(hello_cpp, fv->getNode());
}

TEST_F (FileSystemTest, FileInFolder) {
    Node* test_data = new Folder("./test_data");
    Node* hello_cpp = new File("./test_data/hello.cpp");
    test_data->add(hello_cpp);
    std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"),std::string("hello.cpp")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    test_data->accept(fv);
    ASSERT_EQ(hello_cpp, fv->getNode());
}

TEST_F (FileSystemTest, FileInNestedFolder) {
    Node* test_data = new Folder ("./test_data");
    Node* test_data2 = new Folder ("./test_data/test_data");
    Node* a_out = new File ("./test_data/test_data/a.out");
    Node* b_out = new File("./test_data/test_data/b.out");
    test_data->add(test_data2);
    test_data2->add(a_out);
    test_data2->add(b_out);
    std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("test_data"), std::string("a.out")};
    std::vector<std::string>* names2 = new std::vector<std::string>{std::string("test_data"), std::string("test_data"), std::string("b.out")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    FindNodeByPathnameVisitor* fv2 = new FindNodeByPathnameVisitor(names2);
    test_data->accept(fv);
    test_data->accept(fv2);
    ASSERT_EQ(a_out, fv->getNode());
    ASSERT_EQ(b_out, fv2->getNode());
}

TEST_F (FileSystemTest, Folder) {
    Node* test_data = new Folder ("./test_data");
    std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    test_data->accept(fv);
    ASSERT_EQ(test_data, fv->getNode());
}

// TEST_F (FileSystemTest, FolderInTheSameNameFolder) {
//     Node* test_data = new Folder ("./test_data");
//     Node* test_data2 = new Folder("./test_data/test_data");
//     test_data->add(test_data2);
//     std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("test_data")};
//     FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
//     test_data->accept(fv);
//     ASSERT_EQ(test_data2, fv->getNode());
// }

TEST_F (FileSystemTest, FolderInFolder) {
    Node* test_data = new Folder ("./test_data");
    Node* folder = new Folder("./test_data/folder");
    test_data->add(folder);
    std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("folder")};
    FindNodeByPathnameVisitor* fv = new FindNodeByPathnameVisitor(names);
    test_data->accept(fv);
    ASSERT_EQ(folder, fv->getNode());
}

TEST_F (FileSystemTest, Link){
      Node * hello = new Link("./test_data/hello");
      std::vector<std::string>* names = new std::vector<std::string>{std::string("hello")};
      FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
      hello->accept(fv);
      ASSERT_EQ(hello, fv->getNode());
}

TEST_F (FileSystemTest, LinkInFolder){
      Node * test_data = new Folder ("./test_data");
      Node * hello = new Link("./test_data/hello");
      test_data->add(hello);
      std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("hello")};
      FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
      test_data->accept(fv);
      ASSERT_EQ(hello, fv->getNode());
}

TEST_F (FileSystemTest, nonExistingFileInFileSystem){
      Node * test_data = new Folder ("./test_data");
      std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("helloWorld")};
      FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
      test_data->accept(fv);
      ASSERT_EQ(nullptr, fv->getNode());
}

// TEST_F (FileSystemTest, NodeTypeError)
// {
//   ASSERT_ANY_THROW(new File("./test_data/folder"));//Do not indicate the file path.
//   ASSERT_ANY_THROW(new Folder("./test_data/hello"));//Do not indicate the Folder path.
//   ASSERT_ANY_THROW(new Link("./test_data/hello.cpp"));//Do not indicate the Link path.
// }
//
// TEST_F(FileSystemTest, Size) {
//     ASSERT_EQ(4096, test_data->size());
//     ASSERT_EQ(4096, folder->size());
//     ASSERT_EQ(83, hello_cpp->size());
//     ASSERT_EQ(8432, a_out->size());
//     ASSERT_EQ(12, hello->size());
//     ASSERT_EQ(8432, dynamic_cast<Link *>(hello)->getSource()->size());
//     ASSERT_EQ(3, test_data->numberOfChildren());
// }
//
// TEST_F(FileSystemTest, Visitor) {
//     InfoContentVisitor *icv = new InfoContentVisitor();
//     a_out->accept(icv);
//     ASSERT_EQ(8432, icv->getContentSize());
//     delete icv;
//
//     InfoContentVisitor *icv10 = new InfoContentVisitor();
//     hello->accept(icv10);
//     ASSERT_EQ(8432, icv10->getContentSize());
//     // icv = new InfoContentVisitor("");
//     InfoContentVisitor *icv2 = new InfoContentVisitor();
//     folder->accept(icv2);
//     ASSERT_EQ(8432, icv2->getContentSize());
//
//     InfoContentVisitor *icv3 = new InfoContentVisitor();
//     test_data->accept(icv3);
//     ASSERT_EQ(16947, icv3->getContentSize());
// }
//
// TEST_F(FileSystemTest, NodeIterator) {
//     std::unique_ptr<NodeIterator> it(test_data->createIterator());
//     // NodeIterator * it = test_data->createIterator();
//     it->first();
//     ASSERT_EQ(4096, it->currentItem()->size());
//     it->next();
//     ASSERT_EQ(12, it->currentItem()->size());
//     it->next();
//     ASSERT_EQ(83, it->currentItem()->size());
//     it->next();
//     ASSERT_TRUE(it->isDone());
//     ASSERT_ANY_THROW(it->currentItem());
//     ASSERT_ANY_THROW(it->next());
//
//     // delete it;
// }
//
// TEST_F(FileSystemTest, NodeBuilderOnFile) {
//     NodeBuilder nb;
//     nb.build("test_data/hello.cpp");
//     ASSERT_EQ(83, nb.getRoot()->size());
//
//     nb.build("test_data/hello");
//     ASSERT_EQ(12, nb.getRoot()->size());
//     // ASSERT_EQ(8432, dynamic_cast<Link *>(nb.getRoot())->getSource()->size());
//
//     nb.build("test_data/folder");
//     ASSERT_EQ(4096, nb.getRoot()->size());
//
//     std::unique_ptr<NodeIterator> it(nb.getRoot()->createIterator());
//     it->first();
//     // ASSERT_TRUE(it->isDone());
//     ASSERT_EQ(8432, it->currentItem()->size());
//
//     it->next();
//     ASSERT_TRUE(it->isDone());
//
//     nb.build("test_data");
//     ASSERT_EQ(4096, nb.getRoot()->size());
//     std::unique_ptr<NodeIterator> it1(nb.getRoot()->createIterator());
//     it1->first();
//     ASSERT_EQ(4096, it1->currentItem()->size());
//     it1->next();
//     ASSERT_EQ(12, it1->currentItem()->size());
//     it1->next();
//     ASSERT_EQ(83, it1->currentItem()->size());
//     it1->next();
//     ASSERT_TRUE(it1->isDone());
// }
//
//  TEST_F(FileSystemTest, FindLinkVisitor)
//  {
//      NodeBuilder nb;
//      nb.build("test_data");
//      FindLinkVisitor * flv = new FindLinkVisitor;
//      nb.getRoot()->accept(flv);
//      ASSERT_EQ(1,flv->getLinks().size());
//  }


#endif
