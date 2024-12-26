//
//  tree_test.cpp
//  data_structure
//
//  Created by ChanningTong on 10/21/24.
//

#include "tree_test.hpp"
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
}
TEST_F(BinarySearchTreeTest, RemoveAndFindExtreme) {
    EXPECT_EQ(bst.findMax(),18);
    EXPECT_EQ(bst.findMin(),3);
    bst.remove(18);
    bst.remove(15);
    bst.remove(3);
    EXPECT_EQ(bst.findMax(),12);
    EXPECT_EQ(bst.findMin(),5);
}
TEST_F(QuadTreeTest, InsertAndQuery) {
    EXPECT_TRUE(qt.insert(10, 10,1));
    EXPECT_TRUE(qt.insert(20, 20,2));
    EXPECT_TRUE(qt.insert(30, 30,3));
    std::vector<int> res = qt.queryRange(SpatialRange(0, 0, 100, 100));
    EXPECT_EQ(3, res.size());
    for (int i = 0; i < res.size(); i ++)
        EXPECT_EQ(i+1, res[i]);
    res.clear();
    EXPECT_TRUE(qt.insert(40, 40,3));
    EXPECT_TRUE(qt.insert(50, 50,3));
    EXPECT_TRUE(qt.insert(60, 60,3));
    res  = qt.queryRange(SpatialRange(15, 15, 40, 40));
    EXPECT_EQ(4, res.size());
}
