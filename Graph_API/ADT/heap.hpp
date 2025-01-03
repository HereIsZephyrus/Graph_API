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
    void insert(const Object& x){
        if (size == array.getSize() - 1)
            array.resizeList(size * 2);
        int hole = ++size; // heap index from 1 for a sample symbol
        for (; hole > 1 && x < array[hole/2]; hole/=2)
            array[hole] = array[hole/2];
        array[hole] = x;
    }
    void deleteMin();
    void deleteMin(Object& minItem);
    void makeEmpty();
};
}
#include "heap.tpp"
#endif /* heap_hpp */
