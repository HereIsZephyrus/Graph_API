//
//  disjsets.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#include "disjsets.hpp"

DisjSets::DisjSets(int elementNum){
    s.resizeList(elementNum);
    for (Vector<int>::iterator it = s.begin(); it != s.end(); it++)
        *it = -1;
}
int DisjSets::find(int x) const{
    if (s[x] < 0)
        return x;
    else
        return find(s[x]);
}
int DisjSets::find(int x){
    if (s[x] < 0)
        return x;
    else
        return s[x] = find(s[x]);
}
void DisjSets::unionSets(int root1,int root2){
    if (s[root2] < s[root1]) {
        s[root1] = root2;
    } else {
        if (s[root1] == s[root2])
            s[root1] --; //update height
        s[root2] = root1;
    }
}
