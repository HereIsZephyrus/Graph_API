//
//  tree_test.hpp
//  data_structure
//
//  Created by ChanningTong on 10/21/24.
//

#ifndef tree_test_hpp
#define tree_test_hpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "tree.hpp"
using namespace tcb;
using std::string;
class BinarySearchTreeTest : public ::testing::Test {
protected:
    BinarySearchTree<int> bst;

    void SetUp() override {
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(3);
        bst.insert(7);
        bst.insert(12);
        bst.insert(18);
    }
};
class AVLSearchTreeTest : public ::testing::Test {
protected:
    AVLSearchTree<int> avl;

    void SetUp() override {
        avl.insert(10);
        avl.insert(5);
        avl.insert(15);
        avl.insert(3);
        avl.insert(7);
        avl.insert(12);
        avl.insert(18);
    }
};
#endif /* tree_test_hpp */
