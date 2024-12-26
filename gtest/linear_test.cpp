//
//  linear_test.cpp
//  data_structure
//
//  Created by ChanningTong on 10/20/24.
//

#include "linear_test.hpp"
// vector
TEST_F(IntVectorTest, BasicOperator) {
    EXPECT_THROW(vec.at(static_cast<size_t>(2)), std::out_of_range);
    EXPECT_EQ(vec.isEmpty(), true);
    EXPECT_THROW(vec.pop_back(), std::runtime_error);
    vec.push_back(5);
    EXPECT_EQ(vec.isEmpty(), false);
    vec.push_back(4);
    EXPECT_EQ(vec.back(), 4);
    vec.pop_back();
    EXPECT_EQ(vec.getSize(), 1);
    vec.clear();
    for (int i = 0; i < 5; i++)
        vec.push_back(i);
    EXPECT_EQ(vec.getSize(), 5);
    for (size_t i = 0; i < 5; i++){
        EXPECT_EQ(vec[i], i);
        EXPECT_EQ(vec.at(i), i);
        vec[i] = 1;
    }
    for (Vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
        EXPECT_EQ(*it, 1);
}
TEST_F(IntVectorTest, InitalCheck) {
    vec = Vector<int>(10);
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec.getSize(), 10);
    EXPECT_EQ(vec.back(), 0);
    Vector<int> other(10,2);
    vec = other;
    EXPECT_EQ(vec.getSize(), 10);
    for (Vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
        EXPECT_EQ(*it, 2);
    Vector<int> another(10,3);
    vec = std::move(another);
    EXPECT_EQ(vec.getSize(), 10);
    for (Vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
        EXPECT_EQ(*it, 3);
}
// list
TEST_F(IntListTest, BasicOperator){
    EXPECT_THROW(list.at(static_cast<size_t>(2)), std::out_of_range);
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
    list.push_back(5);
    EXPECT_EQ(list.isEmpty(), false);
    list.push_front(3);
    EXPECT_EQ(list.back(), 5);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.getSize(), 2);
    list.clear();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.at(2), std::out_of_range);
    list.insert(list.begin(), 1);
    list.insert(list.end(), 2);
    list.insert(list.begin(), 0);
    for (size_t i = 0; i < list.getSize(); i++)
        EXPECT_EQ(list.at(i), i);
    EXPECT_EQ(*list.find(2), list.back());
    list.clear();
    list.push_back(2);
    list.push_back(2);
    list.push_back(2);
    for (List<int>::iterator it = list.begin(); it != list.end(); it ++)
        EXPECT_EQ(*it, 2);
}
