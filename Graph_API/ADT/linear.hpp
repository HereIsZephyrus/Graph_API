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
public:
    struct Node{
        Object data;
        Node *prev, *next;
        Node(const Object& d = Object(), Node* p = nullptr, Node* n = nullptr):data(d),prev(p),next(n){}
        ~Node(){prev = nullptr; next = nullptr;}
        Node(const Node& rhs) : data(rhs.data), prev(rhs.prev), next(rhs.next) {}
        Node& operator=(const Node& rhs) {
            if (this == &rhs)
            return *this;
            data = rhs.data;
            prev = rhs.prev;
            next = rhs.next;
            return *this;
        }
    };
protected:
    size_t size;
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
    bool isEmpty() const{return size == 0;}
    size_t getSize() const {return size;}
    void reverse(){
        Node *current = head;
        Node *temp = nullptr;
        while (current != nullptr){
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }
    
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

template <class Object>
class Queue : public List<Object> {
public:
    Queue() : List<Object>() {}
    void enqueue(const Object& x) {this->push_back(x);}
    void dequeue() {
        if (this->isEmpty())
            throw std::out_of_range("Queue is empty");
        this->pop_front();
    }
    const Object& front() const {
        if (this->isEmpty())
            throw std::out_of_range("Queue is empty");
        return List<Object>::front();
    }
    bool isEmpty() const {return List<Object>::isEmpty();}
    size_t getSize() const {return List<Object>::getSize();}
};
}// namespace tcb;
#include "linear.tpp"
#endif /* linear_hpp */
