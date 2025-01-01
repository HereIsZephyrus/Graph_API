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
    //::testing::FLAGS_gtest_filter = "-BinarySearchTreeTest.CopyTest";
    WUSG::Graph<double> graph(10000);
    
    return RUN_ALL_TESTS();
}
