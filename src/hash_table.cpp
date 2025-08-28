#include "hash_table.h"

HashTable::HashTable(size_t initial_bucket_count) 
    : bucket_count_(initial_bucket_count), element_count_(0) {
    buckets_.resize(bucket_count_);
}

// djb2 hash function
size_t HashTable::hash_function(const std::string& key) const {
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c;
    return hash % bucket_count_;
}

void HashTable::insert(const std::string& key, const std::string& value) {
    size_t index = hash_function(key);
    for (auto& kv : buckets_[index]) {
        if (kv.first == key) {
            kv.second = value;  // update if exists
            return;
        }
    }
    buckets_[index].push_back({ key, value });  // insert new
    element_count_++; // increament only when adding new pair
}

std::string HashTable::retrieve(const std::string& key) const {
    size_t index = hash_function(key);
    for (auto& kv : buckets_[index]) {
        if (kv.first == key) {
            return kv.second;
        }
    }
    return "";  // not found
}

void HashTable::remove(const std::string& key) {
    size_t index = hash_function(key);
    size_t before = buckets_[index].size();
    buckets_[index].remove_if([&](auto& kv) { return kv.first == key; });
    size_t after = buckets_[index].size();
    if (after < before) element_count_--;
}

double HashTable::load_factor() const {
    // --> load factor = usage / capacity
    return static_cast<double>(element_count_) / bucket_count_;
}
