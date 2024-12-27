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
int HashTable<Key,Element>::hash(const Key&key, int tableSize){
    int hashVal = calcHash<Key>(key);
    hashVal %= tableSize;
    if (hashVal < 0)
        hashVal += tableSize;
    return hashVal;
}
template <typename Key,typename Element>
HashTable<Key,Element>::~HashTable(){
    clear();
}
template <typename Key,typename Element>
HashTable<Key,Element>::HashTable(int capacity,float maxLoadFactor):
capacity(capacity),maxLoadFactor(maxLoadFactor),size(0){
}
template <typename Key,typename Element>
bool HashTable<Key,Element>::search(const Key&) const{
    
}
template <typename Key,typename Element>
bool HashTable<Key,Element>::insert(const Element&) const{
    HashObject obj = std::make_pair()
    List<HashObject>& orientList = hashList[calcHash(key)];
    if (orientList.find(std::make_pair)) {
        <#statements#>
    }
}
template <typename Key,typename Element>
int HashTable<Key,Element>::remove(const Key&,const Element&){
    List<HashObject>& orientList = hashList[calcHash(key)];
    List<HashObject>::iterator itr = orientList.find(std::make_pair(Key,Element));
    if (itr == orientList.end())
        return 0;
    orientList.remove(itr);
    --size;
    return 1;
}
template <typename Key,typename Element>
void HashTable<Key,Element>::resizeTable(){
    
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
int HashTable<Key,Element>::getBucket(const Key& key) const{return calcHash(key);}
template <typename Key,typename Element>
int getBucketSize(int i) const{
    if (i >= capacity)
        throw std::out_of_range("Index out of range");
    return hashList[i].getSize();
}
