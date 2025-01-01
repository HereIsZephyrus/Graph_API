//
//  main.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/26/24.
//

#include <iostream>
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include "graph_api.hpp"

int main(int argc, char **argv) {
    //::testing::InitGoogleTest(&argc, argv);
    WUSG::Graph<double> graph(87575);
    WUSG::CreateGraphFromFile("/Users/channingtong/Program/Graph_API/usa.txt", graph,true);
    std::cout<<graph.vertexCount()<<' '<<graph.edgeCount()<<std::endl;
    //return RUN_ALL_TESTS();
    return 0;
}
