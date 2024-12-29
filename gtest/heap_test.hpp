//
//  heap_test.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#ifndef heap_test_hpp
#define heap_test_hpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "../Graph_API/ADT/heap.hpp"
using namespace tcb;
using std::string;
template <typename Object>
class HeapTest : public ::testing::Test {
protected:
    Heap<Object> heap;
    HeapTest(){}
    void SetUp() override {}
};
using HeapIntTest = HeapTest<int>;
using HeapStringTest = HeapTest<string>;
#endif /* heap_test_hpp */
