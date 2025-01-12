//
//  heap.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

#ifndef heap_hpp
#define heap_hpp
#include <stdexcept>
#include "linear.hpp"
namespace tcb{
template <typename Object>
class Heap {
    int size;
    Vector<Object> array;
    void percolateDown(int hole);
public:
    explicit Heap(int capacity = 10):size(0){array.resizeList(capacity);};
    ~Heap(){array.clear();}//why I should clear manually?
    bool isEmpty() const{return size == 0;}
    const Object& findMin() const;
    void insert(const Object& x);
    void deleteMin();
    void deleteMin(Object& minItem);
    void makeEmpty();
};
}
#include "heap.tpp"
#endif /* heap_hpp */
