//
//  linear.hpp
//  data_structure
//
//  Created by ChanningTong on 10/10/24.
//

#ifndef linear_hpp
#define linear_hpp

#include <cstring>
#include <string>
#include <stdexcept>
#include <algorithm>
namespace tcb{
template <class Object>
class Vector {
protected:
    size_t size,capacity;
    Object* data;
public:
    enum { SPARE_CAPACITY = 8};
    Vector();
    explicit Vector(size_t initSize,Object initVal = Object());
    ~Vector();
    Vector(const Vector& rhs);
    Vector(Vector && rhs);
    const Vector& operator=(const Vector& rhs);
    
    void reserve(size_t newCapacity);
    void push_back(const Object& x);
    void pop_back();
    
    bool isEmpty() const{return size == 0;}
    size_t getSize() const {return size;}
    size_t getCapacity() const{return capacity;}
    const Object& back(){return data[size-1];}
    
    class iterator;
    //class const_iterator;
    using const_iterator = const iterator;
    iterator begin() {Object* head = &data[0];return iterator(head);}
    iterator end() {Object* head = &data[0];return iterator(head + size);}
    const_iterator begin() const{Object* head = &data[0];return const_iterator::begin(head);}
    const_iterator end() const{Object* head = &data[0];return const_iterator::end(head + size);}
    
    //requuired
    void resizeList(size_t newSize);
    Object& operator[](size_t index);
    const Object& operator[](size_t index) const;
    Object& at(size_t index);
    void clear();
};

template <class Object>
class List {
protected:
    size_t size;
    struct Node{
        Object data;
        Node *prev, *next;
        Node(const Object& d = Object(), Node* p = nullptr, Node* n = nullptr):data(d),prev(p),next(n){}
        ~Node(){prev = nullptr; next = nullptr;}
    };
    Node *head, *tail;
public:
    List();
    ~List();
    List(const List& rhs);
    List(List && rhs);
    const List& operator=(const List& rhs){
        if (this == &rhs)
            return *this;
        clear();
        iterator current = begin();
        for(iterator it = rhs.begin(); it != rhs.end(); it++)
            current = insert(current,*it);
        return *this;
    }
    bool isEmpty(){return size == 0;}
    size_t getSize() const {return size;}
    
    class iterator;
    //class const_iterator;
    using const_iterator = const iterator;
    iterator begin() {return iterator(head->next);}
    iterator end() {return iterator(tail);}
    const_iterator begin() const{return const_iterator(head->next);}
    const_iterator end() const{return const_iterator(tail);}
    const Object& front() const{return head->next->data;}
    const Object& back() const{return tail->prev->data;}
    void push_front(const Object& x);
    void push_back(const Object& x);
    void pop_front();
    void pop_back();
    
    Object& at(size_t index);
    virtual iterator find(const Object& val) const;// the first find value's iter
    
    //required
    iterator insert(iterator it, const Object& x);
    iterator remove(iterator it);
    iterator remove(iterator start,iterator end);
    void clear();
};
}// namespace tcb;
#include "linear.tpp"
#endif /* linear_hpp */
