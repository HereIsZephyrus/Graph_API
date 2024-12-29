//
//  graph_test.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/28/24.
//

#ifndef graph_test_hpp
#define graph_test_hpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "../Graph_API/ADT/graph.hpp"
using namespace tcb;
using std::string;
template <typename V,typename W>
class WUSGraphTest : public ::testing::Test {
protected:
    WUSGraph<V,W> graph;
    WUSGraphTest():graph(10){}
    void SetUp() override {}
};
using WUSGraphIntTest = WUSGraphTest<int,double>;
using WUSGraphStringTest = WUSGraphTest<string,double>;

#endif /* graph_test_hpp */
