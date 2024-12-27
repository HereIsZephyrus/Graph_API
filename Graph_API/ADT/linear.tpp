//
//  linear.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/26/24.
//
using namespace tcb;

//Vector
template <class Object>
Vector<Object>::Vector():size(0),capacity(SPARE_CAPACITY){
    data = new Object[capacity];
};
template <class Object>
Vector<Object>::Vector(size_t initSize,Object initVal):size(initSize){
    capacity = initSize+SPARE_CAPACITY;
    data = new Object[capacity];
    std::fill(data,data+size,initVal);
}
template <class Object>
Vector<Object>::~Vector(){delete [] data;};
template <class Object>
Vector<Object>::Vector(const Vector& rhs) : size(rhs.size),capacity(rhs.capacity){
    data = new Object[capacity];
    std::copy(rhs.data,rhs.data + size,data);
}
template <class Object>
Vector<Object>::Vector(Vector && rhs): size(rhs.size),capacity(rhs.capacity){
    data = rhs.data;
    rhs.data = nullptr;
    rhs.size = 0;
}
template <class Object>
const Vector<Object>& Vector<Object>::operator=(const Vector& rhs){
    if (this == &rhs)
        return *this;
    delete [] data;
    size = rhs.size;
    capacity = rhs.capacity;
    data = new Object[capacity];
    std::copy(rhs.data,rhs.data+size,data);
    return *this;
}

template <class Object>
void Vector<Object>::reserve(size_t newCapacity){
    if (newCapacity < capacity)
        return;
    Object *datum = data;
    capacity = newCapacity;
    data = new Object[capacity];
    std::copy(datum,datum+size,data);
    delete [] datum;
}
template <class Object>
void Vector<Object>::resizeList(size_t newSize){
    if (newSize > capacity)
        reserve(newSize * 2 + 1);
    if (newSize > size)
        std::fill(data + size,data + newSize, Object());
    size = newSize;
}
template <class Object>
void Vector<Object>::push_back(const Object& x){
    if (size == capacity)
        reserve(size * 2 + 1);
    data[size++] = x;
}
template <class Object>
void Vector<Object>::pop_back(){
    if (isEmpty())
        throw std::runtime_error("Pop an empty vector");
    size--;
    return;
}
template <class Object>
void Vector<Object>::clear(){
    size = 0;
    capacity = SPARE_CAPACITY;
    data = new Object[capacity];
}
template <class Object>
Object& Vector<Object>::operator[](size_t index){return data[index];}
template <class Object>
const Object& Vector<Object>::operator[](size_t index) const{return data[index];}
template <class Object>
Object& Vector<Object>::at(size_t index){
    if (index >= size || index < 0)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <class Object>
class Vector<Object>::element_iter{
    // element_iter traits
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Object;
    using pointer = Object *;
    using reference = Object &;
private:
    pointer ptr;
public:
    element_iter(pointer p) : ptr(p){}
    element_iter& operator=(const element_iter& it){ptr = it.ptr; return *this;}
    bool operator == (const element_iter& it) const {return ptr == it.ptr;}
    bool operator != (const element_iter& it) const {return ptr != it.ptr;}
    reference operator *() {return *ptr;}
    element_iter& operator++(){
        ptr++;
        return *this;
    }
    element_iter operator ++(int){
        element_iter ret_ptr = *this;
        ++(*this);
        return ret_ptr;
    }
    element_iter& operator--(){
        ptr--;
        return *this;
    }
    element_iter operator--(int){
        element_iter ret_ptr = *this;
        --(*this);
        return *this;
    }
};

//List
template <class Object>
List<Object>::List():size(0),head(new Node),tail(new Node){
    head->next = tail;
    tail->prev = head;
}
template <class Object>
List<Object>::~List(){
    clear();
    delete tail;
    delete head;
}

template <class Object>
class List<Object>::iterator{
    // iterator traits
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Object;
    using pointer = Node *;
    using reference = value_type &;
private:
    pointer ptr;
public:
    iterator(pointer p){ptr = p;};
    iterator& operator=(const iterator& it){ptr = it.ptr; return *this;}
    bool operator == (const iterator& it) const {return ptr == it.ptr;}
    bool operator != (const iterator& it) const {return ptr != it.ptr;}
    reference& operator *() {return ptr->data;}
    pointer _ptr(){return ptr;}
    iterator& operator++(){
        ptr = ptr->next;
        return *this;
    }
    iterator operator ++(int){
        iterator ret_ptr = *this;
        ++(*this);
        return ret_ptr;
    }
    iterator& operator--(){
        ptr = ptr->prev;
        return *this;
    }
    iterator operator--(int){
        iterator ret_ptr = *this;
        --(*this);
    }
};

template <class Object>
void List<Object>::push_front(const Object& x){insert(begin(),x);}
template <class Object>
void List<Object>::push_back(const Object& x){insert(end(),x);return;}
template <class Object>
void List<Object>::pop_front(){
    if (isEmpty())
        throw std::runtime_error("List is empty");
    remove(begin());
    return;
}
template <class Object>
void List<Object>::pop_back(){
    if (isEmpty())
        throw std::runtime_error("List is empty");
    remove(--end());
    return;
}

template <class Object>
List<Object>::iterator List<Object>::insert(iterator it, const Object& x){
    Node *p = it._ptr();
    size ++;
    p->prev = p->prev->next = new Node(x,p->prev,p);
    return iterator(p->prev);
}
template <class Object>
List<Object>::iterator List<Object>::remove(iterator it){
    if (isEmpty())
        throw std::runtime_error("List is empty");
    Node *p = it._ptr();
    iterator ret_p(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    size --;
    return ret_p;
}
template <class Object>
List<Object>::iterator List<Object>::remove(iterator start,iterator end){
    for (iterator it = start; it!= end;)
        it = remove(it);
    return end;
}
template <class Object>
void List<Object>::clear(){
    iterator it(head->next);
    while (!isEmpty())
        it = remove(it);
}

template <class Object>
Object& List<Object>::at(size_t index){
    if (index >= size)
        throw std::out_of_range("Index out of range");
    iterator current(begin());
    while (index)  { ++current; --index;}
    return *current;
}
template <class Object>
List<Object>::iterator List<Object>::find(const Object& val){// the first find value's iter
    iterator it = begin();
    for (; it != end(); it++)
        if (*it == val)
            return it;
    return it;
}
