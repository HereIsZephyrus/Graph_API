//
//  graph_test.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/28/24.
//

#include "graph_test.hpp"

TEST_F(WUSGraphIntTest, VertexCountInitiallyZero) {
    EXPECT_EQ(graph.vertexCount(), 0);
}

TEST_F(WUSGraphIntTest, AddVertexIncreasesCount) {
    graph.addVertex(1);
    EXPECT_EQ(graph.vertexCount(), 1);
}

TEST_F(WUSGraphIntTest, RemoveVertexDecreasesCount) {
    graph.addVertex(1);
    graph.removeVertex(1);
    EXPECT_EQ(graph.vertexCount(), 0);
}

TEST_F(WUSGraphIntTest, IsVertexReturnsTrueForAddedVertex) {
    graph.addVertex(1);
    EXPECT_TRUE(graph.isVertex(1));
}

TEST_F(WUSGraphIntTest, IsVertexReturnsFalseForNonexistentVertex) {
    EXPECT_FALSE(graph.isVertex(1));
}

TEST_F(WUSGraphIntTest, GetDegreeReturnsCorrectDegree) {
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 1.0);
    EXPECT_EQ(graph.getDegree(1), 1);
}

TEST_F(WUSGraphIntTest, AddEdgeIncreasesEdgeCount) {
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 1.0);
    EXPECT_EQ(graph.edgeCount(), 1);
}

TEST_F(WUSGraphIntTest, RemoveEdgeDecreasesEdgeCount) {
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 1.0);
    graph.removeEdge(1, 2);
    EXPECT_EQ(graph.edgeCount(), 0);
}

TEST_F(WUSGraphIntTest, HasEdgeReturnsTrueForAddedEdge) {
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 1.0);
    EXPECT_TRUE(graph.hasEdge(1, 2));
}

TEST_F(WUSGraphIntTest, HasEdgeReturnsFalseForNonexistentEdge) {
    EXPECT_FALSE(graph.hasEdge(1, 2));
}

TEST_F(WUSGraphIntTest, GetWeightReturnsCorrectWeight) {
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 1.0);
    EXPECT_EQ(graph.getWeight(1, 2), 1.0);
}
TEST_F(WUSGraphIntTest, ComplexGraphOperations) {
    for (int i = 1; i <= 10; ++i)
        graph.addVertex(i);
    graph.addEdge(1, 2, 1.0);
    graph.addEdge(2, 3, 2.0);
    graph.addEdge(3, 4, 3.0);
    graph.addEdge(4, 5, 4.0);
    graph.addEdge(5, 6, 5.0);
    graph.addEdge(6, 7, 6.0);
    graph.addEdge(7, 8, 7.0);
    graph.addEdge(8, 9, 8.0);
    graph.addEdge(9, 10, 9.0);
    graph.addEdge(10, 1, 10.0);
    EXPECT_EQ(graph.vertexCount(), 10);
    EXPECT_EQ(graph.edgeCount(), 10);
    for (int i = 1; i <= 10; ++i)
        EXPECT_EQ(graph.getDegree(i), 2);
    EXPECT_EQ(graph.getWeight(1, 2), 1.0);
    EXPECT_EQ(graph.getWeight(2, 3), 2.0);
    EXPECT_EQ(graph.getWeight(3, 4), 3.0);
    EXPECT_EQ(graph.getWeight(4, 5), 4.0);
    EXPECT_EQ(graph.getWeight(5, 6), 5.0);
    EXPECT_EQ(graph.getWeight(6, 7), 6.0);
    EXPECT_EQ(graph.getWeight(7, 8), 7.0);
    EXPECT_EQ(graph.getWeight(8, 9), 8.0);
    EXPECT_EQ(graph.getWeight(9, 10), 9.0);
    EXPECT_EQ(graph.getWeight(10, 1), 10.0);
    graph.removeEdge(1, 2);
    EXPECT_EQ(graph.edgeCount(), 9);
    EXPECT_FALSE(graph.hasEdge(1, 2));
    graph.removeVertex(5);
    EXPECT_EQ(graph.vertexCount(), 9);
    EXPECT_EQ(graph.edgeCount(), 7);
    EXPECT_FALSE(graph.isVertex(5));
    EXPECT_FALSE(graph.hasEdge(4, 5));
    EXPECT_FALSE(graph.hasEdge(5, 6));
}
TEST_F(WUSGraphStringTest, VertexCountInitiallyZero) {
    EXPECT_EQ(graph.vertexCount(), 0);
}

TEST_F(WUSGraphStringTest, AddVertexIncreasesCount) {
    graph.addVertex("A");
    EXPECT_EQ(graph.vertexCount(), 1);
}

TEST_F(WUSGraphStringTest, RemoveVertexDecreasesCount) {
    graph.addVertex("A");
    graph.removeVertex("A");
    EXPECT_EQ(graph.vertexCount(), 0);
}

TEST_F(WUSGraphStringTest, IsVertexReturnsTrueForAddedVertex) {
    graph.addVertex("A");
    EXPECT_TRUE(graph.isVertex("A"));
}

TEST_F(WUSGraphStringTest, IsVertexReturnsFalseForNonexistentVertex) {
    EXPECT_FALSE(graph.isVertex("A"));
}

TEST_F(WUSGraphStringTest, GetDegreeReturnsCorrectDegree) {
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addEdge("A", "B", 1.0);
    EXPECT_EQ(graph.getDegree("A"), 1);
}

TEST_F(WUSGraphStringTest, AddEdgeIncreasesEdgeCount) {
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addEdge("A", "B", 1.0);
    EXPECT_EQ(graph.edgeCount(), 1);
}

TEST_F(WUSGraphStringTest, RemoveEdgeDecreasesEdgeCount) {
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addEdge("A", "B", 1.0);
    graph.removeEdge("A", "B");
    EXPECT_EQ(graph.edgeCount(), 0);
}

TEST_F(WUSGraphStringTest, HasEdgeReturnsTrueForAddedEdge) {
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addEdge("A", "B", 1.0);
    EXPECT_TRUE(graph.hasEdge("A", "B"));
}

TEST_F(WUSGraphStringTest, HasEdgeReturnsFalseForNonexistentEdge) {
    EXPECT_FALSE(graph.hasEdge("A", "B"));
}

TEST_F(WUSGraphStringTest, GetWeightReturnsCorrectWeight) {
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addEdge("A", "B", 1.0);
    EXPECT_EQ(graph.getWeight("A", "B"), 1.0);
}
