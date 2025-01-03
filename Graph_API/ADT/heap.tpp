//
//  heap.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

template <typename Object>
void Heap<Object>::percolateDown(int hole){
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
template <typename Object>
const Object& Heap<Object>::findMin() const {
    if (isEmpty())
        throw std::out_of_range("heap is empty");
    return array[1];
}
/*
template <typename Object>
void Heap<Object>::insert(const Object& x){
    if (size == array.getSize() - 1)
        array.resizeList(size * 2);
    int hole = ++size; // heap index from 1 for a sample symbol
    for (; hole > 1 && x < array[hole/2]; hole/=2)
        array[hole] = array[hole/2];
    array[hole] = x;
}
*/
template <typename Object>
void Heap<Object>::deleteMin(){
    if (isEmpty())
        throw std::out_of_range("heap is empty");
    array[1] = array[size--];
    percolateDown(1);
}
template <typename Object>
void Heap<Object>::deleteMin(Object& minItem){
    if (isEmpty())
        throw std::out_of_range("heap is empty");
    minItem = array[1];
    array[1] = array[size--];
    percolateDown(1);
}
template <typename Object>
void Heap<Object>::makeEmpty(){
    array.clear();
    size = 0;
}
