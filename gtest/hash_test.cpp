//
//  hash_test.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/27/24.
//

#include "hash_test.hpp"

TEST_F(HashIntTableTest, InsertTest) {
    ASSERT_TRUE(table.insert(1, 1.1));
    ASSERT_TRUE(table.insert(2, 2.2));
    ASSERT_EQ(table.getSize(), 2);
}
TEST_F(HashIntTableTest, SearchTest) {
    table.insert(1, 1.1);
    table.insert(2, 2.2);
    ASSERT_TRUE(table.search(1, 1.1));
    ASSERT_TRUE(table.search(2, 2.2));
    ASSERT_FALSE(table.search(3, 3.3));
}

TEST_F(HashIntTableTest, RemoveTest) {
    table.insert(1, 1.1);
    table.insert(2, 2.2);
    double value;
    ASSERT_EQ(table.remove(1, value), 1);
    ASSERT_EQ(value, 1.1);
    ASSERT_EQ(table.getSize(), 1);
    ASSERT_EQ(table.remove(3, value), 0);
}

TEST_F(HashIntTableTest, ResizeTest) {
    for (int i = 0; i < 20; ++i) {
        table.insert(i, i * 1.1);
    }
    ASSERT_GT(table.getCapacity(), 17);
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
TEST_F(HashIntMapTest, InsertTest) {
    ASSERT_TRUE(map.insert(1, 1.1));
    ASSERT_TRUE(map.insert(2, 2.2));
    ASSERT_EQ(map.getKeySet().size(), 2);
}

TEST_F(HashIntMapTest, GetValueTest) {
    map.insert(1, 1.1);
    map.insert(2, 2.2);
    ASSERT_EQ(map.getValue(1), 1.1);
    ASSERT_EQ(map.getValue(2), 2.2);
}

TEST_F(HashIntMapTest, RemoveTest) {
    map.insert(1, 1.1);
    map.insert(2, 2.2);
    ASSERT_EQ(map.remove(1), 1.1);
    ASSERT_EQ(map.getKeySet().size(), 1);
    ASSERT_EQ(map.getValue(1), double());
}

TEST_F(HashIntMapTest, ContainKeyTest) {
    map.insert(1, 1.1);
    map.insert(2, 2.2);
    ASSERT_TRUE(map.containKey(1));
    ASSERT_TRUE(map.containKey(2));
    ASSERT_FALSE(map.containKey(3));
}

TEST_F(HashStringMapTest, InsertTest) {
    ASSERT_TRUE(map.insert("one", 1.1));
    ASSERT_TRUE(map.insert("two", 2.2));
    ASSERT_EQ(map.getKeySet().size(), 2);
}

TEST_F(HashStringMapTest, GetValueTest) {
    map.insert("one", 1.1);
    map.insert("two", 2.2);
    ASSERT_EQ(map.getValue("one"), 1.1);
    ASSERT_EQ(map.getValue("two"), 2.2);
}

TEST_F(HashStringMapTest, RemoveTest) {
    map.insert("one", 1.1);
    map.insert("two", 2.2);
    ASSERT_EQ(map.remove("one"), 1.1);
    ASSERT_EQ(map.getKeySet().size(), 1);
    ASSERT_EQ(map.getValue("one"), double());
}

TEST_F(HashStringMapTest, ContainKeyTest) {
    map.insert("one", 1.1);
    map.insert("two", 2.2);
    ASSERT_TRUE(map.containKey("one"));
    ASSERT_TRUE(map.containKey("two"));
    ASSERT_FALSE(map.containKey("three"));
}
