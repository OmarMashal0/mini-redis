#include "hash_table.h"

HashTable::HashTable(size_t initialBucketCount) 
    : bucket_count_(initialBucketCount), element_count_(0) {
    buckets_.resize(bucket_count_);
}

size_t HashTable::hashFunction(const std::string& key) const {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % bucket_count_;
}

void HashTable::insert(const std::string& key, const std::string& value) {
    size_t index = hashFunction(key);
    for (auto& kv : buckets_[index]) {
        if (kv.first == key) {
            kv.second = value;
            return;
        }
    }
    buckets_[index].push_back({key, value});
    element_count_++;

    if (loadFactor() > 0.75) {
        rehash(bucket_count_ * 2);
    }
}

std::string HashTable::retrieve(const std::string& key) const {
    size_t index = hashFunction(key);
    for (const auto& kv : buckets_[index]) {
        if (kv.first == key) {
            return kv.second;
        }
    }
    return "";
}

void HashTable::remove(const std::string& key) {
    size_t index = hashFunction(key);
    size_t before = buckets_[index].size();
    buckets_[index].remove_if([&](const auto& kv) { return kv.first == key; });
    size_t after = buckets_[index].size();
    if (after < before) element_count_--;
}

double HashTable::loadFactor() const {
    return static_cast<double>(element_count_) / bucket_count_;
}

void HashTable::rehash(size_t newBucketCount) {
    std::vector<std::list<std::pair<std::string, std::string>>> newBuckets(newBucketCount);

    for (const auto& bucket : buckets_) {
        for (const auto& kv : bucket) {
            unsigned long hash = 5381;
            for (char c : kv.first) {
                hash = ((hash << 5) + hash) + c;
            }
            size_t newIndex = hash % newBucketCount;
            newBuckets[newIndex].push_back(kv);
        }
    }

    buckets_ = std::move(newBuckets);
    bucket_count_ = newBucketCount;
}

