//
//  graph_test.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/28/24.
//
#include <ctime>
#include <cstdlib>
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
    graph.addEdge(1, 3, 1.5);
    graph.addEdge(2, 4, 2.5);
    graph.addEdge(3, 5, 3.5);
    graph.addEdge(4, 6, 4.5);
    graph.addEdge(5, 7, 5.5);
    graph.addEdge(6, 8, 6.5);
    graph.addEdge(7, 9, 7.5);
    graph.addEdge(8, 10, 8.5);
    graph.addEdge(9, 1, 9.5);
    graph.addEdge(10, 2, 10.5);
    EXPECT_EQ(graph.vertexCount(), 10);
    EXPECT_EQ(graph.edgeCount(), 20);
    for (int i = 1; i <= 10; ++i)
        EXPECT_EQ(graph.getDegree(i), 4);
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
    EXPECT_EQ(graph.getWeight(1, 3), 1.5);
    EXPECT_EQ(graph.getWeight(2, 4), 2.5);
    EXPECT_EQ(graph.getWeight(3, 5), 3.5);
    EXPECT_EQ(graph.getWeight(4, 6), 4.5);
    EXPECT_EQ(graph.getWeight(5, 7), 5.5);
    EXPECT_EQ(graph.getWeight(6, 8), 6.5);
    EXPECT_EQ(graph.getWeight(7, 9), 7.5);
    EXPECT_EQ(graph.getWeight(8, 10), 8.5);
    EXPECT_EQ(graph.getWeight(9, 1), 9.5);
    EXPECT_EQ(graph.getWeight(10, 2), 10.5);
    graph.removeEdge(1, 2);
    EXPECT_EQ(graph.edgeCount(), 19);
    EXPECT_FALSE(graph.hasEdge(1, 2));
    graph.removeVertex(5);
    EXPECT_EQ(graph.vertexCount(), 9);
    EXPECT_EQ(graph.edgeCount(), 15);
    EXPECT_FALSE(graph.isVertex(5));
    EXPECT_FALSE(graph.hasEdge(4, 5));
    EXPECT_FALSE(graph.hasEdge(5, 6));
    EXPECT_EQ(graph.getDegree(4), 3);
    EXPECT_EQ(graph.getDegree(6), 3);
    graph.removeEdge(2, 3);
    EXPECT_EQ(graph.edgeCount(), 14);
    EXPECT_FALSE(graph.hasEdge(2, 3));
    graph.addEdge(2, 3, 2.0);
    EXPECT_EQ(graph.edgeCount(), 15);
    EXPECT_TRUE(graph.hasEdge(2, 3));
    graph.removeVertex(10);
    EXPECT_EQ(graph.vertexCount(), 8);
    EXPECT_EQ(graph.edgeCount(), 11);
    EXPECT_FALSE(graph.isVertex(10));
    EXPECT_FALSE(graph.hasEdge(9, 10));
    EXPECT_FALSE(graph.hasEdge(8, 10));
    graph.addVertex(10);
    graph.addEdge(9, 10, 9.0);
    graph.addEdge(8, 10, 8.5);
    EXPECT_EQ(graph.vertexCount(), 9);
    EXPECT_EQ(graph.edgeCount(), 13);
    EXPECT_TRUE(graph.isVertex(10));
    EXPECT_TRUE(graph.hasEdge(9, 10));
    EXPECT_TRUE(graph.hasEdge(8, 10));
}
TEST_F(WUSGraphIntTest, GetNeighborReturnsCorrectNeighbors) {
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2, 1.0);
    graph.addEdge(1, 3, 2.0);
    Vector<std::pair<int,double>> neighbors = graph.getNeighbor(1);
    EXPECT_EQ(neighbors.getSize(), 2);
    EXPECT_TRUE((neighbors[0].first == 2 && neighbors[0].second == 1.0) || 
                (neighbors[0].first == 3 && neighbors[0].second == 2.0));
    EXPECT_TRUE((neighbors[1].first == 2 && neighbors[1].second == 1.0) || 
                (neighbors[1].first == 3 && neighbors[1].second == 2.0));
}

TEST_F(WUSGraphIntTest, GetVerticeReturnsAllVertices) {
    for (int i = 1; i <= 5; ++i)
        graph.addVertex(i);
    std::set<int> vertices = graph.getVertice();
    EXPECT_EQ(vertices.size(), 5);
    for (int i = 1; i <= 5; ++i)
        EXPECT_TRUE(std::find(vertices.begin(), vertices.end(), i) != vertices.end());
}
TEST_F(WUSGraphIntTest, LargeScaleGraphOperations) {
    const int numVertices = 1000;
    const int numEdges = 5000;
    for (int i = 1; i <= numVertices; ++i)
        graph.addVertex(i);
    EXPECT_EQ(graph.vertexCount(), numVertices);
    for (int i = 1; i <= numEdges; ++i) {
        int v1 = rand() % numVertices + 1;
        int v2 = rand() % numVertices + 1;
        double weight = static_cast<double>(rand()) / RAND_MAX;
        if (v1 != v2 && !graph.hasEdge(v1, v2))
            graph.addEdge(v1, v2, weight);
    }
    for (int i = 1; i <= numVertices; ++i) {
        int degree = graph.getDegree(i);
        EXPECT_GE(degree, 0);
        EXPECT_LE(degree, numVertices - 1);
    }
    for (int i = 1; i <= numVertices; ++i) {
        for (int j = i + 1; j <= numVertices; ++j) {
            if (graph.hasEdge(i, j)) {
                double weight = graph.getWeight(i, j);
                EXPECT_GE(weight, 0.0);
                EXPECT_LE(weight, 1.0);
            }
        }
    }
    for (int i = 1; i <= numEdges / 2; ++i) {
        int v1 = rand() % numVertices + 1;
        int v2 = rand() % numVertices + 1;
        if (graph.hasEdge(v1, v2)) {
            graph.removeEdge(v1, v2);
        }
    }
    for (int i = 1; i <= numVertices / 2; ++i) {
        int v = rand() % numVertices + 1;
        if (graph.isVertex(v)) {
            graph.removeVertex(v);
        }
    }
}
TEST_F(WUSGraphStringTest, VertexCountInitiallyZero) {
    EXPECT_EQ(graph.vertexCount(), 0);
}

TEST_F(WUSGraphStringTest, IsVertexReturnsTrueForAddedVertex) {
    EXPECT_FALSE(graph.isVertex("A"));
    graph.addVertex("A");
    EXPECT_TRUE(graph.isVertex("A"));
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

TEST_F(WUSGraphStringTest, GetWeightReturnsCorrectWeight) {
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addEdge("A", "B", 1.0);
    EXPECT_EQ(graph.getWeight("A", "B"), 1.0);
}
TEST_F(WUSGraphStringTest, ComplexGraphOperations) {
    std::vector<std::string> vertices = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    for (const auto& vertex : vertices)
        graph.addVertex(vertex);
    graph.addEdge("A", "B", 1.0);
    graph.addEdge("B", "C", 2.0);
    graph.addEdge("C", "D", 3.0);
    graph.addEdge("D", "E", 4.0);
    graph.addEdge("E", "F", 5.0);
    graph.addEdge("F", "G", 6.0);
    graph.addEdge("G", "H", 7.0);
    graph.addEdge("H", "I", 8.0);
    graph.addEdge("I", "J", 9.0);
    graph.addEdge("J", "A", 10.0);
    graph.addEdge("A", "C", 1.5);
    graph.addEdge("B", "D", 2.5);
    graph.addEdge("C", "E", 3.5);
    graph.addEdge("D", "F", 4.5);
    graph.addEdge("E", "G", 5.5);
    graph.addEdge("F", "H", 6.5);
    graph.addEdge("G", "I", 7.5);
    graph.addEdge("H", "J", 8.5);
    graph.addEdge("I", "A", 9.5);
    graph.addEdge("J", "B", 10.5);
    EXPECT_EQ(graph.vertexCount(), 10);
    EXPECT_EQ(graph.edgeCount(), 20);
    for (const auto& vertex : vertices)
        EXPECT_EQ(graph.getDegree(vertex), 4);
    EXPECT_EQ(graph.getWeight("A", "B"), 1.0);
    EXPECT_EQ(graph.getWeight("B", "C"), 2.0);
    EXPECT_EQ(graph.getWeight("C", "D"), 3.0);
    EXPECT_EQ(graph.getWeight("D", "E"), 4.0);
    EXPECT_EQ(graph.getWeight("E", "F"), 5.0);
    EXPECT_EQ(graph.getWeight("F", "G"), 6.0);
    EXPECT_EQ(graph.getWeight("G", "H"), 7.0);
    EXPECT_EQ(graph.getWeight("H", "I"), 8.0);
    EXPECT_EQ(graph.getWeight("I", "J"), 9.0);
    EXPECT_EQ(graph.getWeight("J", "A"), 10.0);
    EXPECT_EQ(graph.getWeight("A", "C"), 1.5);
    EXPECT_EQ(graph.getWeight("B", "D"), 2.5);
    EXPECT_EQ(graph.getWeight("C", "E"), 3.5);
    EXPECT_EQ(graph.getWeight("D", "F"), 4.5);
    EXPECT_EQ(graph.getWeight("E", "G"), 5.5);
    EXPECT_EQ(graph.getWeight("F", "H"), 6.5);
    EXPECT_EQ(graph.getWeight("G", "I"), 7.5);
    EXPECT_EQ(graph.getWeight("H", "J"), 8.5);
    EXPECT_EQ(graph.getWeight("I", "A"), 9.5);
    EXPECT_EQ(graph.getWeight("J", "B"), 10.5);
    graph.removeEdge("A", "B");
    EXPECT_EQ(graph.edgeCount(), 19);
    EXPECT_FALSE(graph.hasEdge("A", "B"));
    graph.removeVertex("E");
    EXPECT_EQ(graph.vertexCount(), 9);
    EXPECT_EQ(graph.edgeCount(), 15);
    EXPECT_FALSE(graph.isVertex("E"));
    EXPECT_FALSE(graph.hasEdge("D", "E"));
    EXPECT_FALSE(graph.hasEdge("E", "F"));
    EXPECT_EQ(graph.getDegree("D"), 3);
    EXPECT_EQ(graph.getDegree("F"), 3);
    graph.removeEdge("B", "C");
    EXPECT_EQ(graph.edgeCount(), 14);
    EXPECT_FALSE(graph.hasEdge("B", "C"));
    graph.addEdge("B", "C", 2.0);
    EXPECT_EQ(graph.edgeCount(), 15);
    EXPECT_TRUE(graph.hasEdge("B", "C"));
    graph.removeVertex("J");
    EXPECT_EQ(graph.vertexCount(), 8);
    EXPECT_EQ(graph.edgeCount(), 11);
    EXPECT_FALSE(graph.isVertex("J"));
    EXPECT_FALSE(graph.hasEdge("I", "J"));
    EXPECT_FALSE(graph.hasEdge("H", "J"));
    graph.addVertex("J");
    graph.addEdge("I", "J", 9.0);
    graph.addEdge("H", "J", 8.5);
    EXPECT_EQ(graph.vertexCount(), 9);
    EXPECT_EQ(graph.edgeCount(), 13);
    EXPECT_TRUE(graph.isVertex("J"));
    EXPECT_TRUE(graph.hasEdge("I", "J"));
    EXPECT_TRUE(graph.hasEdge("H", "J"));
}
