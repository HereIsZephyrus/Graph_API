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
    void percolateDown(int hole){
        int child;
        Object tmp = array[hole];
        for ( ; hole * 2 <= size; hole = child){
            child = hole * 2;
            if (child != size && array[child + 1] < array[child])
                ++child;
            if (array[child] < tmp)
                array[hole] = array[child];
            else
                break;
        }
        array[hole] = tmp;
    }
public:
    explicit Heap(int capacity = 100){array.reserve(capacity);};
    ~Heap(){
        //why I should clear manually?
        array.clear();
    }
    bool isEmpty() const{return size == 0;}
    const Object& findMin() const {
        if (isEmpty())
            throw std::out_of_range("heap is empty");
        return array[1];
    }
    void insert(const Object& x){
        if (size == array.getSize() - 1)
            array.resizeList(size * 2);
        int hole = ++size; // heap index from 1 for a sample symbol
        for (; hole > 1 && x < array[hole/2]; hole/=2)
            array[hole] = array[hole/2];
        array[hole] = x;
    }
    void deleteMin(){
        if (isEmpty())
            throw std::out_of_range("heap is empty");
        array[1] = array[size--];
        percolateDown(1);
    }
    void deleteMin(Object& minItem){
        if (isEmpty())
            throw std::out_of_range("heap is empty");
        minItem = array[1];
        array[1] = array[size--];
        percolateDown(1);
    }
    void makeEmpty();
};
}
#include "heap.tpp"
#endif /* heap_hpp */
