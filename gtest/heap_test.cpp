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
    for (int i = 1000; i >= 1; --i)
        heap.insert(i);
    EXPECT_EQ(heap.findMin(), 1);
    for (int i = 0; i < 500; ++i)
        heap.deleteMin();
    EXPECT_EQ(heap.findMin(), 501);
    for (int i = 1001; i <= 1500; ++i)
        heap.insert(i);
    EXPECT_EQ(heap.findMin(), 501);
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
    // Insert a large number of elements
    for (char c = 'z'; c >= 'a'; --c) {
        heap.insert(std::string(1, c));
    }
    EXPECT_EQ(heap.findMin(), "a");

    // Delete half of the elements
    for (int i = 0; i < 13; ++i) {
        heap.deleteMin();
    }
    EXPECT_EQ(heap.findMin(), "n");

    // Insert more elements
    for (char c = 'A'; c <= 'M'; ++c) {
        heap.insert(std::string(1, c));
    }
    EXPECT_EQ(heap.findMin(), "A");

    // Delete all elements
    while (!heap.isEmpty()) {
        heap.deleteMin();
    }
    EXPECT_TRUE(heap.isEmpty());

    // Test exception handling
    EXPECT_THROW(heap.deleteMin(), std::out_of_range);
    EXPECT_THROW(heap.findMin(), std::out_of_range);

    // Insert elements again
    heap.insert("banana");
    heap.insert("apple");
    heap.insert("cherry");
    EXPECT_EQ(heap.findMin(), "apple");

    // Delete min with return
    std::string minItem;
    heap.deleteMin(minItem);
    EXPECT_EQ(minItem, "apple");
    EXPECT_EQ(heap.findMin(), "banana");

    // Insert duplicate elements
    heap.insert("banana");
    heap.insert("banana");
    heap.insert("banana");
    EXPECT_EQ(heap.findMin(), "banana");

    // Delete all elements
    while (!heap.isEmpty()) {
        heap.deleteMin();
    }
    EXPECT_TRUE(heap.isEmpty());
}
