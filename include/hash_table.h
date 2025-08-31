#ifndef MINIREDIS_INCLUDE_HASH_TABLE_H_
#define MINIREDIS_INCLUDE_HASH_TABLE_H_

#include <string>
#include <vector>
#include <list>

class HashTable {
private:
    static const size_t kDefaultBucketCount = 16;
    std::vector<std::list<std::pair<std::string, std::string>>> buckets_;
    size_t bucket_count_;
    size_t element_count_;

    size_t hashFunction(const std::string& key) const;
    void rehash(size_t newBucketCount);

public:
    explicit HashTable(size_t initialBucketCount = kDefaultBucketCount);

    void insert(const std::string& key, const std::string& value);
    std::string retrieve(const std::string& key) const;
    void remove(const std::string& key);

    double loadFactor() const;
};

#endif  // MINIREDIS_INCLUDE_HASH_TABLE_H_
