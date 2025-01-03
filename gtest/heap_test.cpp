//
//  heap_test.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#include "heap_test.hpp"

TEST_F(HeapIntTest, InsertAndFindMin) {
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(1);
    EXPECT_EQ(heap.findMin(), 1);
}

TEST_F(HeapIntTest, DeleteMin) {
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(1);
    heap.deleteMin();
    EXPECT_EQ(heap.findMin(), 5);
}

TEST_F(HeapIntTest, DeleteMinWithReturn) {
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(1);
    int minItem;
    heap.deleteMin(minItem);
    EXPECT_EQ(minItem, 1);
    EXPECT_EQ(heap.findMin(), 5);
}

TEST_F(HeapIntTest, IsEmpty) {
    EXPECT_TRUE(heap.isEmpty());
    heap.insert(10);
    EXPECT_FALSE(heap.isEmpty());
}

TEST_F(HeapStringTest, InsertAndFindMin) {
    heap.insert("banana");
    heap.insert("apple");
    heap.insert("cherry");
    EXPECT_EQ(heap.findMin(), "apple");
}

TEST_F(HeapStringTest, DeleteMin) {
    heap.insert("banana");
    heap.insert("apple");
    heap.insert("cherry");
    heap.deleteMin();
    EXPECT_EQ(heap.findMin(), "banana");
}

TEST_F(HeapStringTest, DeleteMinWithReturn) {
    heap.insert("banana");
    heap.insert("apple");
    heap.insert("cherry");
    std::string minItem;
    heap.deleteMin(minItem);
    EXPECT_EQ(minItem, "apple");
    EXPECT_EQ(heap.findMin(), "banana");
}
TEST_F(HeapIntTest, ComprehensiveTest) {
    for (int i = 10000; i >= 1; --i)
        heap.insert(i);
    EXPECT_EQ(heap.findMin(), 1);
    for (int i = 0; i < 5000; ++i)
        heap.deleteMin();
    EXPECT_EQ(heap.findMin(), 5001);
    for (int i = 10001; i <= 15000; ++i)
        heap.insert(i);
    EXPECT_EQ(heap.findMin(), 5001);
    while (!heap.isEmpty())
        heap.deleteMin();
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_THROW(heap.deleteMin(), std::out_of_range);
    EXPECT_THROW(heap.findMin(), std::out_of_range);

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    EXPECT_EQ(heap.findMin(), 5);

    int minItem;
    heap.deleteMin(minItem);
    EXPECT_EQ(minItem, 5);
    EXPECT_EQ(heap.findMin(), 10);
    heap.insert(10);
    heap.insert(10);
    heap.insert(10);
    EXPECT_EQ(heap.findMin(), 10);
    
    while (!heap.isEmpty())
        heap.deleteMin();
    EXPECT_TRUE(heap.isEmpty());
}

TEST_F(HeapStringTest, ComprehensiveTest) {
    for (char c = 'z'; c >= 'a'; --c)
        heap.insert(std::string(1, c));
    EXPECT_EQ(heap.findMin(), "a");
    for (int i = 0; i < 13; ++i)
        heap.deleteMin();
    EXPECT_EQ(heap.findMin(), "n");
    for (char c = 'A'; c <= 'M'; ++c)
        heap.insert(std::string(1, c));
    EXPECT_EQ(heap.findMin(), "A");
    while (!heap.isEmpty())
        heap.deleteMin();
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_THROW(heap.deleteMin(), std::out_of_range);
    EXPECT_THROW(heap.findMin(), std::out_of_range);
    heap.insert("banana");
    heap.insert("apple");
    heap.insert("cherry");
    EXPECT_EQ(heap.findMin(), "apple");
    std::string minItem;
    heap.deleteMin(minItem);
    EXPECT_EQ(minItem, "apple");
    EXPECT_EQ(heap.findMin(), "banana");
    heap.insert("banana");
    heap.insert("banana");
    heap.insert("banana");
    EXPECT_EQ(heap.findMin(), "banana");

    while (!heap.isEmpty())
        heap.deleteMin();
    EXPECT_TRUE(heap.isEmpty());
}
