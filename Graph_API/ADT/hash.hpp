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
namespace tcb{
template <typename T> int calcHash(const T& key);
template <typename Key,typename Element>
class HashTable {
    using HashObject = std::pair<Key,Element>;
    using Bucket = List<HashObject>;
    float maxLoadFactor;
    size_t capacity,size;
    size_t hash(const Key&key, int tableSize);
    Vector<Bucket> hashList;
    bool insert(const HashObject&);
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
    int getCapacity() const;
    int getSize() const;
    int getBucket(const Key&) const;
    int getBucketSize(int i) const;
};
}
template <typename Key,typename Element>
class HashMap : public HashTable<Key,Element>{
    std::set<Key> keySet;
public:
    HashMap(float maxLoadFactor = 0.7,int capacity = 17):HashTable(maxLoadFactor,capacity){};
    //required
    const Element& getValue(const Key&key);
    bool insert(const Key&,const Element&) override;
    Element remove(const Key&);
    int remove(const Key&,Element&) override;
    bool containKey(const Key& key) const;
    const std::set<K> getKeySet() {return keySet;}
};
#include "hash.tpp"
#endif /* hash_hpp */
