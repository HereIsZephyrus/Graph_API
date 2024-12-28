//
//  hash.hpp
//  Graph_API
//
//  Created by ChanningTong on 12/27/24.
//

#ifndef hash_hpp
#define hash_hpp
#define VALUE_HASH 2654435761U
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <map>
#include <set>
#include "linear.hpp"
using std::string;
typedef std::pair<int,int> VertexPair;
namespace tcb{
template <typename T>
inline int calcHash(const T& key);
template <typename Key,typename Element>
class HashTable {
protected:
    using HashObject = std::pair<Key,Element>;
    class Bucket;
    float maxLoadFactor;
    size_t capacity,size;
    size_t hash(const Key&key) const;
    Vector<Bucket> hashList;
    bool insert(const HashObject&);
    size_t nextPrime(size_t currentCapacity);
    constexpr static  Element zeroElement = Element();
public:
    HashTable(float maxLoadFactor = 0.7,int capacity = 17);
    ~HashTable();
    void setMaxLoadFactor(float loadFactor){maxLoadFactor = loadFactor;}
    //required
    bool search(const Key&,const Element&) const;
    virtual bool insert(const Key&,const Element&);
    virtual int remove(const Key&,Element&); // return the mount of remove item
    void resizeTable();
    void clear();
    size_t getCapacity() const;
    size_t getSize() const;
    int getBucket(const Key&) const;
    int getBucketSize(int i) const;
};
}
template <typename Key,typename Element>
class HashMap : public HashTable<Key,Element>{
protected:
    std::set<Key> keySet;
    using Bucket = HashTable<Key,Element>::Bucket;
    Element& getRefValue(const Key&key);
public:
    HashMap(float maxLoadFactor = 0.7,int capacity = 17):HashTable<Key,Element>(maxLoadFactor,capacity){};
    //required
    const Element& getValue(const Key&key) const;// return const Element& will return a local refer, I don't know how to solve
    bool insert(const Key& key,const Element& element) override;
    Element remove(const Key& key);
    bool containKey(const Key& key) const{return keySet.contains(key);};
    const std::set<Key> getKeySet() {return keySet;}
    Element& operator[](const Key& key);
    const Element& operator[](const Key& key) const;
    Element& at(const Key& key);
};
#include "hash.tpp"
#endif /* hash_hpp */
