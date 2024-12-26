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
namespace tcb{
template <class Object>
class Array {
protected:
    size_t size;
    Object* data;
public:
    Array();
    explicit Array(size_t setSize,Object initVal = Object());
    ~Array();
    Array(const Array& rhs);
    Array(Array && rhs);
    const Array& operator= (const Array& rhs);
    
    Object& operator[](size_t index){ return data[index];} // fast access
    const Object& operator[] (size_t index) const{return data[index];}
    Object& at(size_t index){ // security access
        if (index >= size || index < 0)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    
    size_t getSize() const {return size;}
    void fill(const Object& val){std::fill(data,data+size, val);}
    void set(size_t index,const Object& val){
        if (index >= size || index < 0)
            throw std::out_of_range("Index out of range");
        data[index] = val;
    }
    
    class element_iter;
    using iterator = element_iter;
    iterator begin() {Object* head = &data[0];return iterator(head);}
    iterator end() {Object* head = &data[0];return iterator(head + size);}
    using const_iterator = const iterator;
    const_iterator begin() const{Object* head = &data[0];return const_iterator::begin(head);}
    const_iterator end() const{Object* head = &data[0];return const_iterator::end(head + size);}
};

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
    
    Object& operator[](size_t index){return data[index];}
    const Object& operator[](size_t index) const{return data[index];}
    Object& at(size_t index){
        if (index >= size || index < 0)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    
    void reserve(size_t newCapacity);
    void resize(size_t newSize);
    void push_back(const Object& x);
    void pop_back();
    void clear();
    
    bool isEmpty() const{return size == 0;}
    size_t getSize() const {return size;}
    size_t getCapacity() const{return capacity;}
    const Object& back(){return data[size-1];}
    
    class element_iter;
    using iterator = element_iter;
    iterator begin() {Object* head = &data[0];return iterator(head);}
    iterator end() {Object* head = &data[0];return iterator(head + size);}
    using const_iterator = const iterator;
    const_iterator begin() const{Object* head = &data[0];return const_iterator::begin(head);}
    const_iterator end() const{Object* head = &data[0];return const_iterator::end(head + size);}
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
    bool isEmpty(){return size == 0;}
    size_t getSize() const {return size;}
    
    class iterator;
    iterator begin() {return iterator(head->next);}
    iterator end() {return iterator(tail);}
    const Object& front() const{return head->next->data;}
    const Object& back() const{return tail->prev->data;}
    void push_front(const Object& x);
    void push_back(const Object& x);
    void pop_front();
    void pop_back();
    iterator insert(iterator it, const Object& x);
    iterator earse(iterator it);
    iterator earse(iterator start,iterator end);
    void clear();
    
    Object& at(size_t index);
    iterator find(const Object& val);// the first find value's iter
};
}// namespace tcb;
#include "linear.tpp"
#endif /* linear_hpp */
