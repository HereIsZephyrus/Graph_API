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
    if (argc > 1){
        std::string program_type = argv[1];
        if (program_type == "utest"){
            ::testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }
    }
    WUSG::Graph<double> graph(87575);
    WUSG::CreateGraphFromFile("/Users/channingtong/Program/Graph_API/usa.txt", graph,true);
    std::cout<<graph.vertexCount()<<' '<<graph.edgeCount()<<std::endl;
    return 0;
}
