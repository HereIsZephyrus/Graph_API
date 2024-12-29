//
//  function_test.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#include "function_test.hpp"

TEST_F(GraphAPITest, CreateGraphFromFile) {
    WUSG::CreateGraphFromFile("/Users/channingtong/Program/Graph_API/gtest/test_basic_input.txt", graph);
    EXPECT_EQ(graph.vertexCount(), 5);
    EXPECT_EQ(graph.edgeCount(), 6);
    EXPECT_TRUE(graph.isVertex("A"));
    EXPECT_TRUE(graph.isVertex("B"));
    EXPECT_TRUE(graph.isVertex("C"));
    EXPECT_TRUE(graph.hasEdge("A", "B"));
    EXPECT_FALSE(graph.hasEdge("B", "C"));
    EXPECT_TRUE(graph.hasEdge("A", "E"));
    EXPECT_TRUE(graph.hasEdge("D", "B"));
    EXPECT_DOUBLE_EQ(graph.getWeight("A", "B"), 1.0);
    EXPECT_DOUBLE_EQ(graph.getWeight("B", "D"), 3.0);
}
