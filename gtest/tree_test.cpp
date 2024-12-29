//
//  tree_test.cpp
//  data_structure
//
//  Created by ChanningTong on 10/21/24.
//

#include "tree_test.hpp"
#include "../Graph_API/ADT/tree.hpp"
TEST_F(BinarySearchTreeTest, containsValuesTest) {
    using tr = tcb::BinarySearchTree<int>;
    EXPECT_TRUE(bst.contains(10));
    EXPECT_TRUE(bst.contains(5));
    EXPECT_TRUE(bst.contains(15));
    EXPECT_TRUE(bst.contains(3));
    EXPECT_TRUE(bst.contains(7));
    EXPECT_TRUE(bst.contains(12));
    EXPECT_TRUE(bst.contains(18));
    EXPECT_FALSE(bst.contains(1));
    EXPECT_FALSE(bst.contains(20));
    EXPECT_FALSE(bst.contains(8));
    //std::cout<<tr::preorder<<bst<<std::endl;
    //std::cout<<tr::inorder<<bst<<std::endl;
    //std::cout<<tr::postorder<<bst<<std::endl;
}
TEST_F(BinarySearchTreeTest, CopyTest) {
    BinarySearchTree<int> another = bst;
    EXPECT_TRUE(another.contains(10));
    EXPECT_TRUE(another.contains(5));
    EXPECT_TRUE(another.contains(15));
    EXPECT_TRUE(another.contains(3));
    EXPECT_TRUE(another.contains(7));
    EXPECT_TRUE(another.contains(12));
    EXPECT_TRUE(another.contains(18));
    EXPECT_FALSE(another.contains(1));
    EXPECT_FALSE(another.contains(20));
    EXPECT_FALSE(another.contains(8));
}
TEST_F(BinarySearchTreeTest, InsertAndSearch) {
    bst.insert(11);
    EXPECT_TRUE(bst.contains(11));
    bst.insert(1);
    EXPECT_TRUE(bst.contains(1));
    bst.insert(6);
    EXPECT_TRUE(bst.contains(6));
    bst.insert(14);
    EXPECT_TRUE(bst.contains(14));
    bst.insert(4);
    EXPECT_TRUE(bst.contains(4));
    bst.insert(8);
    EXPECT_TRUE(bst.contains(8));
    bst.insert(13);
    EXPECT_TRUE(bst.contains(13));
    bst.insert(17);
    EXPECT_TRUE(bst.contains(17));
    bst.insert(0);
    EXPECT_TRUE(bst.contains(0));
    bst.insert(2);
    EXPECT_TRUE(bst.contains(2));
    bst.insert(9);
    EXPECT_TRUE(bst.contains(9));
    bst.insert(16);
    EXPECT_TRUE(bst.contains(16));
    bst.insert(19);
    EXPECT_TRUE(bst.contains(19));
    bst.insert(20);
    EXPECT_TRUE(bst.contains(20));
    bst.insert(21);
    EXPECT_TRUE(bst.contains(21));
    bst.insert(22);
    EXPECT_TRUE(bst.contains(22));
    bst.insert(23);
    EXPECT_TRUE(bst.contains(23));
    bst.insert(24);
    EXPECT_TRUE(bst.contains(24));
    bst.insert(25);
    EXPECT_TRUE(bst.contains(25));
    bst.insert(26);
    EXPECT_TRUE(bst.contains(26));
    bst.insert(27);
    EXPECT_TRUE(bst.contains(27));
    bst.insert(28);
    EXPECT_TRUE(bst.contains(28));
    bst.insert(29);
    EXPECT_TRUE(bst.contains(29));
    bst.insert(30);
    EXPECT_TRUE(bst.contains(30));
}
TEST_F(BinarySearchTreeTest, RemoveAndFindExtreme) {
    EXPECT_EQ(bst.findMax(), 18);
    EXPECT_EQ(bst.findMin(), 3);
    bst.remove(18);
    EXPECT_FALSE(bst.contains(18));
    EXPECT_EQ(bst.findMax(), 15);
    bst.remove(15);
    EXPECT_FALSE(bst.contains(15));
    EXPECT_EQ(bst.findMax(), 12);
    bst.remove(3);
    EXPECT_FALSE(bst.contains(3));
    EXPECT_EQ(bst.findMin(), 5);
    bst.remove(5);
    EXPECT_FALSE(bst.contains(5));
    EXPECT_EQ(bst.findMin(), 7);
    bst.remove(7);
    EXPECT_FALSE(bst.contains(7));
    EXPECT_EQ(bst.findMin(), 10);
    bst.remove(10);
    EXPECT_FALSE(bst.contains(10));
    EXPECT_EQ(bst.findMin(), 12);
    bst.remove(12);
    EXPECT_FALSE(bst.contains(12));
}
