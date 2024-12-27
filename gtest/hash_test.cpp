//
//  hash_test.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/27/24.
//

#include "hash_test.hpp"

TEST_F(HashIntTableTest, InsertTest) {
    ASSERT_TRUE(vec.insert(1, 1.1));
    ASSERT_TRUE(vec.insert(2, 2.2));
    ASSERT_EQ(vec.getSize(), 2);
}
/*
TEST_F(HashIntTableTest, SearchTest) {
    vec.insert(1, 1.1);
    vec.insert(2, 2.2);
    ASSERT_TRUE(vec.search(1, 1.1));
    ASSERT_TRUE(vec.search(2, 2.2));
    ASSERT_FALSE(vec.search(3, 3.3));
}

TEST_F(HashIntTableTest, RemoveTest) {
    vec.insert(1, 1.1);
    vec.insert(2, 2.2);
    double value;
    ASSERT_EQ(vec.remove(1, value), 1);
    ASSERT_EQ(value, 1.1);
    ASSERT_EQ(vec.getSize(), 1);
    ASSERT_EQ(vec.remove(3, value), 0);
}

TEST_F(HashIntTableTest, ResizeTest) {
    for (int i = 0; i < 20; ++i) {
        vec.insert(i, i * 1.1);
    }
    ASSERT_GT(vec.getCapacity(), 17);
}

TEST_F(HashStringTableTest, InsertTest) {
    HashTable<string, double> strTable;
    ASSERT_TRUE(strTable.insert("one", 1.1));
    ASSERT_TRUE(strTable.insert("two", 2.2));
    ASSERT_EQ(strTable.getSize(), 2);
}

TEST_F(HashStringTableTest, SearchTest) {
    HashTable<string, double> strTable;
    strTable.insert("one", 1.1);
    strTable.insert("two", 2.2);
    ASSERT_TRUE(strTable.search("one", 1.1));
    ASSERT_TRUE(strTable.search("two", 2.2));
    ASSERT_FALSE(strTable.search("three", 3.3));
}

TEST_F(HashStringTableTest, RemoveTest) {
    HashTable<string, double> strTable;
    strTable.insert("one", 1.1);
    strTable.insert("two", 2.2);
    double value;
    ASSERT_EQ(strTable.remove("one", value), 1);
    ASSERT_EQ(value, 1.1);
    ASSERT_EQ(strTable.getSize(), 1);
    ASSERT_EQ(strTable.remove("three", value), 0);
}
*/
