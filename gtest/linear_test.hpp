//
//  linear_test.hpp
//  data_structure
//
//  Created by ChanningTong on 10/20/24.
//

#ifndef linear_test_hpp
#define linear_test_hpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "../Graph_API/ADT/linear.hpp"
using namespace tcb;
using std::string;
template<class Object>
class VectorTest : public ::testing::Test {
protected:
    Vector<Object> vec;
    VectorTest(){}
    void SetUp() override {}
};
using IntVectorTest = VectorTest<int>;

template<class Object>
class ListTest : public ::testing::Test {
protected:
    List<Object> list;
    ListTest(){}
    void SetUp() override {}
};
using IntListTest = ListTest<int>;
#endif /* linear_test_hpp */
