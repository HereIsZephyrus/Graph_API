//
//  linear_test.cpp
//  data_structure
//
//  Created by ChanningTong on 10/20/24.
//

#include "linear_test.hpp"

// array
TEST(ArrayTest, GetOutOfBounds) {
    Array<int> list(5);
    EXPECT_THROW(list.at(static_cast<size_t>(6)), std::out_of_range);
    EXPECT_THROW(list.at(static_cast<size_t>(-1)), std::out_of_range);
    EXPECT_THROW(list.set(static_cast<size_t>(6),10), std::out_of_range);
    EXPECT_THROW(list.set(static_cast<size_t>(-1),10), std::out_of_range);
}
TEST(ArrayTest, Equals) {
    Array<int> raw(5),changable(5,3),tomove(5,9),unchangable(6);
    EXPECT_EQ(raw[0], 0);
    raw = changable;
    EXPECT_EQ(raw[0], 3);
    Array<int> tocopy(raw);
    EXPECT_EQ(tocopy.getSize(), 5);
    EXPECT_EQ(tocopy[0], 3);
    raw = std::move(tomove);
    EXPECT_EQ(raw[0], 9);
    EXPECT_THROW(raw = unchangable, std::length_error);
}
TEST_F(IntArrayTest, SetElement) {
    constexpr int defaultVal = 5;
    constexpr int changedVal = 8;
    list.fill(defaultVal);
    for (Array<int>::iterator it = list.begin(); it != list.end(); it++){
        EXPECT_EQ(*it, defaultVal);
        counter++;
    }
    EXPECT_EQ(counter, 10);
    list.set(5, changedVal);
    EXPECT_EQ(list.at(5), changedVal);
    EXPECT_EQ(list[5], changedVal);
}
TEST_F(DoubleArrayTest, SetElement) {
    constexpr double defaultVal = 4.7689869;
    constexpr double changedVal = 8976.8976;
    list.fill(defaultVal);
    for (Array<double>::iterator it = list.begin(); it != list.end(); it++){
        EXPECT_DOUBLE_EQ(*it, defaultVal);
        counter++;
    }
    EXPECT_EQ(counter, 10);
    list.set(5, changedVal);
    EXPECT_EQ(list.at(5), changedVal);
    EXPECT_EQ(list[5], changedVal);
}
TEST_F(CharArrayTest, SetElement) {
    constexpr char defaultVal = 'a';
    constexpr char changedVal = 'B';
    list.fill(defaultVal);
    for (Array<char>::iterator it = list.begin(); it != list.end(); it++){
        EXPECT_EQ(*it, defaultVal);
        counter++;
    }
    EXPECT_EQ(counter, 10);
    list.set(5, changedVal);
    EXPECT_EQ(list.at(5), changedVal);
    EXPECT_EQ(list[5], changedVal);
}
TEST_F(StringArrayTest, SetElement) {
    constexpr string defaultVal = "default_value";
    constexpr string changedVal = "changed_value";
    list.fill(defaultVal);
    for (Array<string>::iterator it = list.begin(); it != list.end(); it++){
        EXPECT_STREQ((*it).c_str(), defaultVal.c_str());
        counter++;
    }
    list.set(5, changedVal);
    EXPECT_STREQ((list.at(5)).c_str(), changedVal.c_str());
    EXPECT_EQ(list[5], changedVal);
}

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
