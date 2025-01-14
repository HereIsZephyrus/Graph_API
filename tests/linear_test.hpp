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
#include "linear.hpp"
using namespace tcb;
using std::string;
template<class Object>
class VectorTest : public ::testing::Test {
protected:
    Vector<Object> vec;
    VectorTest(){}
    void SetUp() override {}
};
using VectorIntTest = VectorTest<int>;
using VectorDoubleTest = VectorTest<double>;
using VectorStringTest = VectorTest<string>;

template<class Object>
class ListTest : public ::testing::Test {
protected:
    List<Object> list;
    ListTest(){}
    void SetUp() override {}
};
using ListIntTest = ListTest<int>;
using ListDoubleTest = ListTest<double>;
using ListStringTest = ListTest<string>;

class QueueTest : public ::testing::Test {
protected:
    Queue<int> queue;
    QueueTest(){}
    void SetUp() override {}
};
#endif /* linear_test_hpp */
