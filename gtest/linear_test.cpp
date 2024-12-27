//
//  linear_test.cpp
//  data_structure
//
//  Created by ChanningTong on 10/20/24.
//

#include "linear_test.hpp"
// vector
TEST_F(VectorIntTest, DestructorAndRange){
    EXPECT_THROW(vec.at(static_cast<size_t>(2)), std::out_of_range);
    EXPECT_EQ(vec.isEmpty(), true);
    EXPECT_THROW(vec.pop_back(), std::runtime_error);
}

TEST_F(VectorIntTest, BasicOperator) {
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
TEST_F(VectorIntTest, InitalCheck) {
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
// vector
TEST_F(VectorIntTest, ReserveAndCapacity) {
    vec.reserve(20);
    EXPECT_EQ(vec.getCapacity(), 20);
    vec.reserve(5);
    EXPECT_EQ(vec.getCapacity(), 20); // Capacity should not decrease
}

TEST_F(VectorIntTest, PushBackAndPopBack) {
    vec.push_back(10);
    EXPECT_EQ(vec.back(), 10);
    EXPECT_EQ(vec.getSize(), 1);
    vec.push_back(20);
    EXPECT_EQ(vec.back(), 20);
    EXPECT_EQ(vec.getSize(), 2);
    vec.pop_back();
    EXPECT_EQ(vec.back(), 10);
    EXPECT_EQ(vec.getSize(), 1);
    vec.pop_back();
    EXPECT_EQ(vec.isEmpty(), true);
    EXPECT_THROW(vec.pop_back(), std::runtime_error); // Popping from empty vector
}

TEST_F(VectorIntTest, ResizeList) {
    vec.resizeList(5);
    EXPECT_EQ(vec.getSize(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(vec[i], 0);
    }
    vec.resizeList(2);
    EXPECT_EQ(vec.getSize(), 2);
    vec.resizeList(10);
    EXPECT_EQ(vec.getSize(), 10);
    for (size_t i = 2; i < 10; i++) {
        EXPECT_EQ(vec[i], 0);
    }
}

TEST_F(VectorIntTest, IteratorFunctionality) {
    for (int i = 0; i < 5; i++)
        vec.push_back(i);
    Vector<int>::iterator it = vec.begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 1);
    it++;
    EXPECT_EQ(*it, 2);
    --it;
    EXPECT_EQ(*it, 1);
    it--;
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(it != vec.end(), true);
    it = vec.end();
    EXPECT_EQ(it == vec.end(), true);
}
// vector double
TEST_F(VectorDoubleTest, BasicOperator) {
    vec.push_back(5.5);
    EXPECT_EQ(vec.isEmpty(), false);
    vec.push_back(4.4);
    EXPECT_EQ(vec.back(), 4.4);
    vec.pop_back();
    EXPECT_EQ(vec.getSize(), 1);
    vec.clear();
    for (int i = 0; i < 5; i++)
        vec.push_back(static_cast<double>(i) + 0.1);
    EXPECT_EQ(vec.getSize(), 5);
    for (size_t i = 0; i < 5; i++){
        EXPECT_EQ(vec[i], static_cast<double>(i) + 0.1);
        EXPECT_EQ(vec.at(i), static_cast<double>(i) + 0.1);
        vec[i] = 1.1;
    }
    for (Vector<double>::iterator it = vec.begin(); it != vec.end(); it++)
        EXPECT_EQ(*it, 1.1);
}

TEST_F(VectorDoubleTest, ReserveAndCapacity) {
    vec.reserve(20);
    EXPECT_EQ(vec.getCapacity(), 20);
    vec.reserve(5);
    EXPECT_EQ(vec.getCapacity(), 20); // Capacity should not decrease
}

TEST_F(VectorDoubleTest, PushBackAndPopBack) {
    vec.push_back(10.1);
    EXPECT_EQ(vec.back(), 10.1);
    EXPECT_EQ(vec.getSize(), 1);
    vec.push_back(20.2);
    EXPECT_EQ(vec.back(), 20.2);
    EXPECT_EQ(vec.getSize(), 2);
    vec.pop_back();
    EXPECT_EQ(vec.back(), 10.1);
    EXPECT_EQ(vec.getSize(), 1);
    vec.pop_back();
    EXPECT_EQ(vec.isEmpty(), true);
    EXPECT_THROW(vec.pop_back(), std::runtime_error); // Popping from empty vector
}

TEST_F(VectorDoubleTest, ResizeList) {
    vec.resizeList(5);
    EXPECT_EQ(vec.getSize(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(vec[i], 0.0);
    }
    vec.resizeList(2);
    EXPECT_EQ(vec.getSize(), 2);
    vec.resizeList(10);
    EXPECT_EQ(vec.getSize(), 10);
    for (size_t i = 2; i < 10; i++) {
        EXPECT_EQ(vec[i], 0.0);
    }
}

TEST_F(VectorDoubleTest, IteratorFunctionality) {
    for (int i = 0; i < 5; i++)
        vec.push_back(static_cast<double>(i) + 0.1);
    Vector<double>::iterator it = vec.begin();
    EXPECT_EQ(*it, 0.1);
    ++it;
    EXPECT_EQ(*it, 1.1);
    it++;
    EXPECT_EQ(*it, 2.1);
    --it;
    EXPECT_EQ(*it, 1.1);
    it--;
    EXPECT_EQ(*it, 0.1);
    EXPECT_EQ(it != vec.end(), true);
    it = vec.end();
    EXPECT_EQ(it == vec.end(), true);
}

// vector string
TEST_F(VectorStringTest, BasicOperator) {
    vec.push_back("hello");
    EXPECT_EQ(vec.isEmpty(), false);
    vec.push_back("world");
    EXPECT_EQ(vec.back(), "world");
    vec.pop_back();
    EXPECT_EQ(vec.getSize(), 1);
    vec.clear();
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        vec.push_back(word);
    EXPECT_EQ(vec.getSize(), 5);
    for (size_t i = 0; i < 5; i++){
        EXPECT_EQ(vec[i], words[i]);
        EXPECT_EQ(vec.at(i), words[i]);
        vec[i] = "test";
    }
    for (Vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++)
        EXPECT_EQ(*it, "test");
}

TEST_F(VectorStringTest, ReserveAndCapacity) {
    vec.reserve(20);
    EXPECT_EQ(vec.getCapacity(), 20);
    vec.reserve(5);
    EXPECT_EQ(vec.getCapacity(), 20); // Capacity should not decrease
}

TEST_F(VectorStringTest, PushBackAndPopBack) {
    vec.push_back("first");
    EXPECT_EQ(vec.back(), "first");
    EXPECT_EQ(vec.getSize(), 1);
    vec.push_back("second");
    EXPECT_EQ(vec.back(), "second");
    EXPECT_EQ(vec.getSize(), 2);
    vec.pop_back();
    EXPECT_EQ(vec.back(), "first");
    EXPECT_EQ(vec.getSize(), 1);
    vec.pop_back();
    EXPECT_EQ(vec.isEmpty(), true);
    EXPECT_THROW(vec.pop_back(), std::runtime_error); // Popping from empty vector
}

TEST_F(VectorStringTest, ResizeList) {
    vec.resizeList(5);
    EXPECT_EQ(vec.getSize(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(vec[i], "");
    }
    vec.resizeList(2);
    EXPECT_EQ(vec.getSize(), 2);
    vec.resizeList(10);
    EXPECT_EQ(vec.getSize(), 10);
    for (size_t i = 2; i < 10; i++) {
        EXPECT_EQ(vec[i], "");
    }
}

TEST_F(VectorStringTest, IteratorFunctionality) {
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        vec.push_back(word);
    Vector<std::string>::iterator it = vec.begin();
    EXPECT_EQ(*it, "one");
    ++it;
    EXPECT_EQ(*it, "two");
    it++;
    EXPECT_EQ(*it, "three");
    --it;
    EXPECT_EQ(*it, "two");
    it--;
    EXPECT_EQ(*it, "one");
    EXPECT_EQ(it != vec.end(), true);
    it = vec.end();
    EXPECT_EQ(it == vec.end(), true);
}
// vector
TEST_F(VectorIntTest, CopyConstructor) {
    for (int i = 0; i < 5; i++)
        vec.push_back(i);
    Vector<int> copy(vec);
    EXPECT_EQ(copy.getSize(), vec.getSize());
    for (size_t i = 0; i < vec.getSize(); i++) {
        EXPECT_EQ(copy[i], vec[i]);
    }
}

TEST_F(VectorIntTest, AssignmentOperator) {
    Vector<int> other;
    for (int i = 0; i < 5; i++)
        other.push_back(i);
    vec = other;
    EXPECT_EQ(vec.getSize(), other.getSize());
    for (size_t i = 0; i < other.getSize(); i++) {
        EXPECT_EQ(vec[i], other[i]);
    }
}

TEST_F(VectorIntTest, MoveConstructor) {
    for (int i = 0; i < 5; i++)
        vec.push_back(i);
    Vector<int> moved(std::move(vec));
    EXPECT_EQ(moved.getSize(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(moved[i], i);
    }
    EXPECT_EQ(vec.getSize(), 0);
}

// vector double
TEST_F(VectorDoubleTest, CopyConstructor) {
    for (int i = 0; i < 5; i++)
        vec.push_back(static_cast<double>(i) + 0.1);
    Vector<double> copy(vec);
    EXPECT_EQ(copy.getSize(), vec.getSize());
    for (size_t i = 0; i < vec.getSize(); i++) {
        EXPECT_EQ(copy[i], vec[i]);
    }
}

TEST_F(VectorDoubleTest, AssignmentOperator) {
    Vector<double> other;
    for (int i = 0; i < 5; i++)
        other.push_back(static_cast<double>(i) + 0.1);
    vec = other;
    EXPECT_EQ(vec.getSize(), other.getSize());
    for (size_t i = 0; i < other.getSize(); i++) {
        EXPECT_EQ(vec[i], other[i]);
    }
}

TEST_F(VectorDoubleTest, MoveConstructor) {
    for (int i = 0; i < 5; i++)
        vec.push_back(static_cast<double>(i) + 0.1);
    Vector<double> moved(std::move(vec));
    EXPECT_EQ(moved.getSize(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(moved[i], static_cast<double>(i) + 0.1);
    }
    EXPECT_EQ(vec.getSize(), 0);
}

// vector string
TEST_F(VectorStringTest, CopyConstructor) {
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        vec.push_back(word);
    Vector<std::string> copy(vec);
    EXPECT_EQ(copy.getSize(), vec.getSize());
    for (size_t i = 0; i < vec.getSize(); i++) {
        EXPECT_EQ(copy[i], vec[i]);
    }
}

TEST_F(VectorStringTest, AssignmentOperator) {
    Vector<std::string> other;
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        other.push_back(word);
    vec = other;
    EXPECT_EQ(vec.getSize(), other.getSize());
    for (size_t i = 0; i < other.getSize(); i++) {
        EXPECT_EQ(vec[i], other[i]);
    }
}

TEST_F(VectorStringTest, MoveConstructor) {
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        vec.push_back(word);
    Vector<std::string> moved(std::move(vec));
    EXPECT_EQ(moved.getSize(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(moved[i], words[i]);
    }
    EXPECT_EQ(vec.getSize(), 0);
}

// list
TEST_F(ListIntTest, BasicOperator){
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
TEST_F(ListIntTest, PushFrontAndBack) {
    list.push_front(1);
    EXPECT_EQ(list.front(), 1);
    list.push_back(2);
    EXPECT_EQ(list.back(), 2);
    list.push_front(0);
    EXPECT_EQ(list.front(), 0);
    list.push_back(3);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.getSize(), 4);
}

TEST_F(ListIntTest, PopFrontAndBack) {
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    list.pop_back();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
    EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST_F(ListIntTest, AtFunction) {
    for (int i = 0; i < 5; i++)
        list.push_back(i);
    for (size_t i = 0; i < 5; i++)
        EXPECT_EQ(list.at(i), i);
    EXPECT_THROW(list.at(5), std::out_of_range);
}

TEST_F(ListIntTest, FindFunction) {
    for (int i = 0; i < 5; i++)
        list.push_back(i);
    List<int>::iterator it = list.find(3);
    EXPECT_EQ(*it, 3);
    it = list.find(5);
    EXPECT_EQ(it, list.end());
}

TEST_F(ListIntTest, InsertFunction) {
    list.push_back(1);
    list.push_back(3);
    List<int>::iterator it = list.insert(list.find(3), 2);
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(list.at(1), 2);
    it = list.insert(list.begin(), 0);
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(list.front(), 0);
}

TEST_F(ListIntTest, RemoveFunction) {
    for (int i = 0; i < 5; i++)
        list.push_back(i);
    List<int>::iterator it = list.remove(list.find(2));
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(list.getSize(), 4);
    it = list.remove(list.find(0), list.find(4));
    EXPECT_EQ(*it, 4);
    EXPECT_EQ(list.getSize(), 1);
}

TEST_F(ListIntTest, ClearFunction) {
    for (int i = 0; i < 5; i++)
        list.push_back(i);
    list.clear();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_EQ(list.getSize(), 0);
}
// list double
TEST_F(ListDoubleTest, BasicOperator){
    EXPECT_THROW(list.at(static_cast<size_t>(2)), std::out_of_range);
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
    list.push_back(5.5);
    EXPECT_EQ(list.isEmpty(), false);
    list.push_front(3.3);
    EXPECT_EQ(list.back(), 5.5);
    EXPECT_EQ(list.front(), 3.3);
    EXPECT_EQ(list.getSize(), 2);
    list.clear();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.at(2), std::out_of_range);
    list.insert(list.begin(), 1.1);
    list.insert(list.end(), 2.2);
    list.insert(list.begin(), 0.0);
    for (size_t i = 0; i < list.getSize(); i++)
        EXPECT_EQ(list.at(i), static_cast<double>(i) * 1.1);
    EXPECT_EQ(*list.find(2.2), list.back());
    list.clear();
    list.push_back(2.2);
    list.push_back(2.2);
    list.push_back(2.2);
    for (List<double>::iterator it = list.begin(); it != list.end(); it ++)
        EXPECT_EQ(*it, 2.2);
}

TEST_F(ListDoubleTest, PushFrontAndBack) {
    list.push_front(1.1);
    EXPECT_EQ(list.front(), 1.1);
    list.push_back(2.2);
    EXPECT_EQ(list.back(), 2.2);
    list.push_front(0.0);
    EXPECT_EQ(list.front(), 0.0);
    list.push_back(3.3);
    EXPECT_EQ(list.back(), 3.3);
    EXPECT_EQ(list.getSize(), 4);
}

TEST_F(ListDoubleTest, PopFrontAndBack) {
    list.push_back(1.1);
    list.push_back(2.2);
    list.push_back(3.3);
    list.pop_front();
    EXPECT_EQ(list.front(), 2.2);
    list.pop_back();
    EXPECT_EQ(list.back(), 2.2);
    list.pop_back();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
    EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST_F(ListDoubleTest, AtFunction) {
    for (int i = 0; i < 5; i++)
        list.push_back(static_cast<double>(i) + 0.1);
    for (size_t i = 0; i < 5; i++)
        EXPECT_EQ(list.at(i), static_cast<double>(i) + 0.1);
    EXPECT_THROW(list.at(5), std::out_of_range);
}

TEST_F(ListDoubleTest, FindFunction) {
    for (int i = 0; i < 5; i++)
        list.push_back(static_cast<double>(i) + 0.1);
    List<double>::iterator it = list.find(3.1);
    EXPECT_EQ(*it, 3.1);
    it = list.find(5.1);
    EXPECT_EQ(it, list.end());
}

TEST_F(ListDoubleTest, InsertFunction) {
    list.push_back(1.1);
    list.push_back(3.3);
    List<double>::iterator it = list.insert(list.find(3.3), 2.2);
    EXPECT_EQ(*it, 2.2);
    EXPECT_EQ(list.at(1), 2.2);
    it = list.insert(list.begin(), 0.0);
    EXPECT_EQ(*it, 0.0);
    EXPECT_EQ(list.front(), 0.0);
}

TEST_F(ListDoubleTest, RemoveFunction) {
    for (int i = 0; i < 5; i++)
        list.push_back(static_cast<double>(i) + 0.1);
    List<double>::iterator it = list.remove(list.find(2.1));
    EXPECT_EQ(*it, 3.1);
    EXPECT_EQ(list.getSize(), 4);
    it = list.remove(list.find(0.1), list.find(4.1));
    EXPECT_EQ(*it, 4.1);
    EXPECT_EQ(list.getSize(), 1);
}

TEST_F(ListDoubleTest, ClearFunction) {
    for (int i = 0; i < 5; i++)
        list.push_back(static_cast<double>(i) + 0.1);
    list.clear();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_EQ(list.getSize(), 0);
}

// list string
TEST_F(ListStringTest, BasicOperator){
    EXPECT_THROW(list.at(static_cast<size_t>(2)), std::out_of_range);
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
    list.push_back("hello");
    EXPECT_EQ(list.isEmpty(), false);
    list.push_front("world");
    EXPECT_EQ(list.back(), "hello");
    EXPECT_EQ(list.front(), "world");
    EXPECT_EQ(list.getSize(), 2);
    list.clear();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.at(2), std::out_of_range);
    list.insert(list.begin(), "first");
    list.insert(list.end(), "second");
    list.insert(list.begin(), "zero");
    std::vector<std::string> words = {"zero", "first", "second"};
    for (size_t i = 0; i < list.getSize(); i++)
        EXPECT_EQ(list.at(i), words[i]);
    EXPECT_EQ(*list.find("second"), list.back());
    list.clear();
    list.push_back("repeat");
    list.push_back("repeat");
    list.push_back("repeat");
    for (List<std::string>::iterator it = list.begin(); it != list.end(); it ++)
        EXPECT_EQ(*it, "repeat");
}

TEST_F(ListStringTest, PushFrontAndBack) {
    list.push_front("first");
    EXPECT_EQ(list.front(), "first");
    list.push_back("second");
    EXPECT_EQ(list.back(), "second");
    list.push_front("zero");
    EXPECT_EQ(list.front(), "zero");
    list.push_back("third");
    EXPECT_EQ(list.back(), "third");
    EXPECT_EQ(list.getSize(), 4);
}

TEST_F(ListStringTest, PopFrontAndBack) {
    list.push_back("first");
    list.push_back("second");
    list.push_back("third");
    list.pop_front();
    EXPECT_EQ(list.front(), "second");
    list.pop_back();
    EXPECT_EQ(list.back(), "second");
    list.pop_back();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
    EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST_F(ListStringTest, AtFunction) {
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        list.push_back(word);
    for (size_t i = 0; i < 5; i++)
        EXPECT_EQ(list.at(i), words[i]);
    EXPECT_THROW(list.at(5), std::out_of_range);
}

TEST_F(ListStringTest, FindFunction) {
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        list.push_back(word);
    List<std::string>::iterator it = list.find("three");
    EXPECT_EQ(*it, "three");
    it = list.find("six");
    EXPECT_EQ(it, list.end());
}

TEST_F(ListStringTest, InsertFunction) {
    list.push_back("first");
    list.push_back("third");
    List<std::string>::iterator it = list.insert(list.find("third"), "second");
    EXPECT_EQ(*it, "second");
    EXPECT_EQ(list.at(1), "second");
    it = list.insert(list.begin(), "zero");
    EXPECT_EQ(*it, "zero");
    EXPECT_EQ(list.front(), "zero");
}

TEST_F(ListStringTest, RemoveFunction) {
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        list.push_back(word);
    List<std::string>::iterator it = list.remove(list.find("three"));
    EXPECT_EQ(*it, "four");
    EXPECT_EQ(list.getSize(), 4);
    it = list.remove(list.find("one"), list.find("five"));
    EXPECT_EQ(*it, "five");
    EXPECT_EQ(list.getSize(), 1);
}

TEST_F(ListStringTest, ClearFunction) {
    std::vector<std::string> words = {"one", "two", "three", "four", "five"};
    for (const auto& word : words)
        list.push_back(word);
    list.clear();
    EXPECT_EQ(list.isEmpty(), true);
    EXPECT_EQ(list.getSize(), 0);
}
