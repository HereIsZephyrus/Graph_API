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
    EXPECT_EQ(WUSG::MaxDegree(graph), 3);
    EXPECT_TRUE(graph.isVertex("A"));
    EXPECT_TRUE(graph.isVertex("B"));
    EXPECT_TRUE(graph.isVertex("C"));
    EXPECT_TRUE(graph.hasEdge("A", "B"));
    EXPECT_FALSE(graph.hasEdge("B", "C"));
    EXPECT_TRUE(graph.hasEdge("A", "E"));
    EXPECT_TRUE(graph.hasEdge("D", "B"));
    EXPECT_DOUBLE_EQ(graph.getWeight("A", "B"), 1.0);
    EXPECT_DOUBLE_EQ(graph.getWeight("B", "D"), 3.0);
    
    graph.removeEdge("A", "B");
    EXPECT_FALSE(graph.hasEdge("A", "B"));
    graph.addEdge("B", "C", 2.5);
    EXPECT_TRUE(graph.hasEdge("B", "C"));
    EXPECT_DOUBLE_EQ(graph.getWeight("B", "C"), 2.5);

    graph.removeVertex("E");
    EXPECT_FALSE(graph.isVertex("E"));
    EXPECT_EQ(WUSG::MaxDegree(graph), 2);
    graph.addVertex("F");
    EXPECT_TRUE(graph.isVertex("F"));
    graph.addEdge("F", "C", 4.0);
    EXPECT_TRUE(graph.hasEdge("F", "C"));
    EXPECT_DOUBLE_EQ(graph.getWeight("F", "C"), 4.0);
    graph.addEdge("F", "D", 5.0);
    EXPECT_TRUE(graph.hasEdge("F", "D"));
    EXPECT_DOUBLE_EQ(graph.getWeight("F", "D"), 5.0);
    graph.removeEdge("F", "C");
    EXPECT_FALSE(graph.hasEdge("F", "C"));
    graph.removeVertex("F");
    EXPECT_FALSE(graph.isVertex("F"));

    graph.addEdge("B", "C", 1.5);
    EXPECT_TRUE(graph.hasEdge("B", "C"));
    EXPECT_DOUBLE_EQ(graph.getWeight("B", "C"), 1.5);

    graph.removeEdge("B", "C");
    EXPECT_FALSE(graph.hasEdge("B", "C"));

    graph.addEdge("A", "D", 2.0);
    EXPECT_TRUE(graph.hasEdge("A", "D"));
    EXPECT_DOUBLE_EQ(graph.getWeight("A", "D"), 2.0);

    graph.removeVertex("D");
    EXPECT_FALSE(graph.isVertex("D"));
    EXPECT_FALSE(graph.hasEdge("A", "D"));
    EXPECT_FALSE(graph.hasEdge("F", "D"));
}
