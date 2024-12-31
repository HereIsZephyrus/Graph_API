//
//  disjsets.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#ifndef disjsets_hpp
#define disjsets_hpp
#include "linear.hpp"
namespace tcb{
class DisjSets {
    Vector<int> s;
public:
    explicit DisjSets(int elementNum);
    int find(int x) const;
    int find(int x);
    void unionSets(int root1,int root2);
    int countSets() const;
};
}
#endif /* disjsets_hpp */
