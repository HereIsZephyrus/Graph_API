//
//  hash.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/27/24.
//

using namespace tcb;
template <>
int calcHash(const string& key){
    int hashVal = 0;
    for (int i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];
    return hashVal;
}
template <>
int calcHash(int key) {
    size_t hashVal = key * VALUE_HASH;
    return static_cast<int>(hashVal);
}

template <>
int calcHash(size_t key) {
    size_t hashVal = key * VALUE_HASH;
    return static_cast<int>(hashVal);
}

template <>
int calcHash(long long key) {
    uint64_t hashVal = static_cast<uint64_t>(key);
    hashVal ^= (hashVal >> 33);
    hashVal *= 0xff51afd7ed558ccdULL;
    hashVal ^= (hashVal >> 33);
    hashVal *= 0xc4ceb9fe1a85ec53ULL;
    hashVal ^= (hashVal >> 33);
    return static_cast<int>(hashVal);
}

template <>
int calcHash(float key) {
    if (key == 0.0f) return 0;
    if (key == -0.0f) return 0;
    uint32_t bits;
    std::memcpy(&bits, &key, sizeof(key));
    return static_cast<int>(bits * VALUE_HASH);
}

template <>
int calcHash(double key) {
    if (key == 0.0) return 0;
    if (key == -0.0) return 0;
    uint64_t bits;
    std::memcpy(&bits, &key, sizeof(key));

    bits ^= (bits >> 33);
    bits *= 0xff51afd7ed558ccdULL;
    bits ^= (bits >> 33);
    bits *= 0xc4ceb9fe1a85ec53ULL;
    bits ^= (bits >> 33)
    return static_cast<int>(bits);
}

template <typename Key,typename Element>
size_t HashTable<Key,Element>::hash(const Key&key, int tableSize){
    int hashVal = calcHash<Key>(key);
    hashVal %= tableSize;
    if (hashVal < 0)
        hashVal += tableSize;
    return static_cast<size_t>(hashVal);
}
template <typename Key,typename Element>
HashTable<Key,Element>::~HashTable(){
    clear();
}
template <typename Key,typename Element>
HashTable<Key,Element>::HashTable(float maxLoadFactor,int capacity):
capacity(capacity),maxLoadFactor(maxLoadFactor),size(0){
    hashList.resize(capacity);
}
template <typename Key,typename Element>
bool HashTable<Key,Element>::search(const Key& key,const Element& element) const{
    List<HashObject>& orientList = hashList[hash(key)];
    HashObject obj = std::make_pair(key,element);
    List<HashObject>::iterator itr = orientList.find(obj);
    if (itr==orientList.end())
        return false;
    return true;
}
template <typename Key,typename Element>
bool HashTable<Key,Element>::insert(const HashObject& obj){
    List<HashObject>& orientList = hashList[hash(key)];
    List<HashObject>::iterator itr = orientList.find(obj);
    if (itr!=orientList.end())
        return false;
    orientList.insert(itr,obj);
    ++size;
    if (size / capacity > maxLoadFactor)
        resizeTable();
    return true;
}
template <typename Key,typename Element>
bool HashTable<Key,Element>::insert(const Key& key,const Element&element){
    HashObject obj = std::make_pair(key,element);
    return insert(obj);
}
template <typename Key,typename Element>
int HashTable<Key,Element>::remove(const Key&,const Element&){
    List<HashObject>& orientList = hashList[hash(key)];
    List<HashObject>::iterator itr = orientList.find(std::make_pair(Key,Element));
    if (itr == orientList.end())
        return 0;
    orientList.remove(itr);
    --size;
    return 1;
}
template <typename Key,typename Element>
void HashTable<Key,Element>::resizeTable(){
    Vector<Bucket> oldHashList = hashList;
    clear();
    capacity = nextPrime(capacity * 2);
    hashList.resize(capacity);
    size = 0;
    for (Node bucket = hashList.begin(); bucket != hashList.end(); bucket++){
        for (List<HashObject>::iterator it = bucket->begin(); it != bucke->end(); it++)
            insert(*itr++);
    }
}
template <typename Key,typename Element>
void HashTable<Key,Element>::clear(){
    for (Node bucket = hashList.begin(); bucket != hashList.end(); bucket++)
        bucket->clear();
}

template <typename Key,typename Element>
int HashTable<Key,Element>::getCapacity() const{return capacity;}
template <typename Key,typename Element>
int HashTable<Key,Element>::getSize() const{return size;}
template <typename Key,typename Element>
int HashTable<Key,Element>::getBucket(const Key& key) const{return hash(key);}
template <typename Key,typename Element>
int getBucketSize(int i) const{
    if (i >= capacity)
        throw std::out_of_range("Index out of range");
    return hashList[i].getSize();
}
