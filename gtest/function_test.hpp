//
//  function_test.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#ifndef function_test_hpp
#define function_test_hpp
#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <sstream>
#include "graph_api.hpp"

class GraphAPITest : public ::testing::Test {
protected:
    tcb::WUSGraph<std::string, double> graph;
    void SetUp() override {}
    void TearDown() override {}
    GraphAPITest():graph(10){};
};
class APIDataTest : public ::testing::Test {
protected:
    WUSG::Graph<double> graph;
    void SetUp() override {}
    void TearDown() override {}
    APIDataTest():graph(10){};
};
#endif /* function_test_hpp */
