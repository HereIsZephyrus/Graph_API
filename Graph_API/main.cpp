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
#include "hash.hpp"

//template int tcb::calcHash<base::Vertex<double>>(const base::Vertex<double>&);
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    WUSG::Graph<double> graph(10000);
    
    return RUN_ALL_TESTS();
}
