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
#include "linear.hpp"
using std::string;
namespace tcb{
template <typename T> int calcHash(const T& key);
template <typename Key,typename Element>
class HashTable {
    using HashObject = std::pair<Key,Element>;
    using Bucket = List<HashObject>;
    float maxLoadFactor;
    int capacity,size;
    int hash(const Key&key, int tableSize);
    Vector<Bucket> hashList;
public:
    HashTable(int capacity = 17,float maxLoadFactor = 0.7);
    ~HashTable();
    //required
    bool search(const Key&) const;
    bool insert(const Key&) const;
    int remove(const Key&,const Element&); // return the mount of remove item
    void resizeTable();
    void clear();
    int getCapacity() const;
    int getSize() const;
    int getBucket(const Key&) const;
    int getBucketSize(int i) const;
};
}
#include "hash.tpp"
#endif /* hash_hpp */
