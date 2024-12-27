//
//  hash_test.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/27/24.
//

#ifndef hash_test_hpp
#define hash_test_hpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "../Graph_API/ADT/hash.hpp"
using namespace tcb;
using std::string;
template <typename Key,typename Element>
class HashTableTest : public ::testing::Test {
protected:
    HashTable<Key,Element> vec;
    HashTableTest(){}
    void SetUp() override {}
};
using HashIntTableTest = HashTableTest<int,double>;
using HashStringTableTest = HashTableTest<string,double>;
#endif /* hash_test_hpp */
