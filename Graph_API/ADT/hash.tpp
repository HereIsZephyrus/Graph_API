//
//  hash.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/27/24.
//

namespace tcb{
template <>
int calcHash(const string& key){
    int hashVal = 0;
    for (int i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];
    return hashVal;
}
template <>
int calcHash(const int& key) {
    size_t hashVal = key * VALUE_HASH;
    return static_cast<int>(hashVal);
}

template <>
int calcHash(const size_t& key) {
    size_t hashVal = key * VALUE_HASH;
    return static_cast<int>(hashVal);
}

template <>
int calcHash(const long long& key) {
    uint64_t hashVal = static_cast<uint64_t>(key);
    hashVal ^= (hashVal >> 33);
    hashVal *= 0xff51afd7ed558ccdULL;
    hashVal ^= (hashVal >> 33);
    hashVal *= 0xc4ceb9fe1a85ec53ULL;
    hashVal ^= (hashVal >> 33);
    return static_cast<int>(hashVal);
}

template <>
int calcHash(const float& key) {
    if (key == 0.0f) return 0;
    if (key == -0.0f) return 0;
    uint32_t bits;
    std::memcpy(&bits, &key, sizeof(key));
    return static_cast<int>(bits * VALUE_HASH);
}

template <>
int calcHash(const double& key) {
    if (key == 0.0) return 0;
    if (key == -0.0) return 0;
    uint64_t bits;
    std::memcpy(&bits, &key, sizeof(key));
    
    bits ^= (bits >> 33);
    bits *= 0xff51afd7ed558ccdULL;
    bits ^= (bits >> 33);
    bits *= 0xc4ceb9fe1a85ec53ULL;
    bits ^= (bits >> 33);
    return static_cast<int>(bits);
}
}
using namespace tcb;
template <typename Key,typename Element>
size_t HashTable<Key,Element>::hash(const Key&key) const{
    int hashVal = calcHash<Key>(key);
    hashVal %= capacity;
    if (hashVal < 0)
        hashVal += capacity;
    return static_cast<size_t>(hashVal);
}
template <typename Key,typename Element>
size_t HashTable<Key,Element>::nextPrime(size_t currentCapacity){
    size_t current = currentCapacity;
    current += 3 - currentCapacity%4;
    int maxIter = 20;
    while (maxIter--){
        bool isPrime = true;
        for (int i = 2; i * i < current; i++)
            if (current % i == 0){
                isPrime = false;
                break;
            }
        if (isPrime)    return current;
        current +=4;
    }
    return currentCapacity;
}
template <typename Key,typename Element>
HashTable<Key,Element>::~HashTable(){
    clear();
}
template <typename Key,typename Element>
HashTable<Key,Element>::HashTable(float maxLoadFactor,int capacity):
capacity(capacity),maxLoadFactor(maxLoadFactor),size(0){
    hashList.resizeList(capacity);
}
template <typename Key,typename Element>
bool HashTable<Key,Element>::search(const Key& key,const Element& element) const{
    const Bucket& orientList = hashList[hash(key)];
    HashObject obj = std::make_pair(key,element);
    typename Bucket::const_iterator itr = orientList.find(obj);
    if (itr==orientList.end())
        return false;
    return true;
}
template <typename Key,typename Element>
bool HashTable<Key,Element>::insert(const HashObject& obj){
    Bucket& orientList = hashList[hash(obj.first)];
    typename Bucket::iterator itr = orientList.find(obj);
    if (itr!=orientList.end())
        return false;
    orientList.insert(itr,obj);
    ++size;
    if (static_cast<float>(size) / capacity > maxLoadFactor)
        resizeTable();
    return true;
}
template <typename Key,typename Element>
bool HashTable<Key,Element>::insert(const Key& key,const Element&element){
    HashObject obj = std::make_pair(key,element);
    return insert(obj);
}
template <typename Key,typename Element>
int HashTable<Key,Element>::remove(const Key& key,Element& element){
    Bucket& orientList = hashList[hash(key)];
    typename Bucket::iterator itr = orientList.find(std::make_pair(key,element));
    if (itr == orientList.end())
        return 0;
    element = (*itr).second;
    orientList.remove(itr);
    --size;
    return 1;
}
template <typename Key,typename Element>
void HashTable<Key,Element>::resizeTable(){
    Vector<Bucket> oldHashList = hashList;
    clear();
    capacity = nextPrime(capacity * 2);
    hashList.resizeList(capacity);
    for (typename Vector<Bucket>::iterator bucket = oldHashList.begin(); bucket != oldHashList.end(); bucket++){
        for (typename Bucket::iterator it = bucket->begin(); it != bucket->end(); it++)
            insert(*it);
    }
}
template <typename Key,typename Element>
void HashTable<Key,Element>::clear(){
    for (typename Vector<Bucket>::iterator bucket = hashList.begin(); bucket != hashList.end(); bucket++)
        bucket->clear();
}

template <typename Key,typename Element>
size_t HashTable<Key,Element>::getCapacity() const{return capacity;}
template <typename Key,typename Element>
size_t HashTable<Key,Element>::getSize() const{return size;}
template <typename Key,typename Element>
int HashTable<Key,Element>::getBucket(const Key& key) const{return hash(key);}
template <typename Key,typename Element>
int HashTable<Key,Element>::getBucketSize(int i) const{
    if (i >= capacity)
        throw std::out_of_range("Index out of range");
    return hashList[i].getSize();
}
template <typename Key,typename Element>
class HashTable<Key,Element>::Bucket : public List<HashObject>{
public:
    using iterator = List<HashObject>::iterator;
    Bucket():List<HashObject>(){}
    iterator find(const HashObject& val) const override{
        iterator it = this->begin();
        for (; it != this->end(); it++)
            if ((*it).first == val.first)
                return it;
        return it;
    }
};
template <typename Key,typename Element>
Element HashMap<Key,Element>::getValue(const Key&key){
    if (!keySet.contains(key))
        return Element();
    const Bucket& orientList = this->hashList[this->hash(key)];
    for (typename Bucket::iterator itr = orientList.begin(); itr != orientList.end(); itr++){
        if ((*itr).first == key)
            return (*itr).second;
    }
    return Element();
}
template <typename Key,typename Element>
bool HashMap<Key,Element>::insert(const Key& key,const Element& element){
    if (keySet.contains(key))
        remove(key);
    keySet.insert(key);
    return HashTable<Key,Element>::insert(key, element);
}
template <typename Key,typename Element>
Element HashMap<Key,Element>::remove(const Key& key){
    Bucket& orientList = this->hashList[this->hash(key)];
    for (typename Bucket::iterator itr = orientList.begin(); itr != orientList.end(); itr++){
        if ((*itr).first == key){
            Element value = (*itr).second;
            orientList.remove(itr);
            --this->size;
            keySet.erase(key);
            return value;
        }
    }
    return Element();
}
template <typename Key,typename Element>
Element& HashMap<Key,Element>::operator[](const Key& key){
    return getValue(key);
}
template <typename Key,typename Element>
const Element& HashMap<Key,Element>::operator[](const Key& key) const{
    return getValue(key);
}
template <typename Key,typename Element>
Element& HashMap<Key,Element>::at(const Key& key){
    if (!containKey(key))
        throw std::out_of_range("Don't have this key yet.'");
    return getValue(key);
}
