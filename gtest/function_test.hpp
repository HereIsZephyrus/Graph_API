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
#include "../Graph_API/graph_api.hpp"
#include "../Graph_API/ADT/graph.hpp"

class GraphAPITest : public ::testing::Test {
protected:
    tcb::WUSGraph<std::string, double> graph;
    void SetUp() override {}
    void TearDown() override {}
    GraphAPITest():graph(10){};
};
#endif /* function_test_hpp */
