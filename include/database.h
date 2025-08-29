#ifndef MINIREDIS_INCLUDE_DATABASE_H_
#define MINIREDIS_INCLUDE_DATABASE_H_

#include <string>
#include <vector>
#include "hash_table.h"
#include "trie.h"
#include "lru_cache.h"

class Database {
private:
    HashTable store_;
    Trie trie_;
    LRUCache cache_;

public:
    explicit Database(size_t cache_capacity = 5) : cache_(cache_capacity) {}

    void insert(const std::string& key, const std::string& value);
    std::string retrieve(const std::string& key);
    void remove(const std::string& key);

    double load_factor() const;
    size_t bucket_count() const { return store_.bucket_count(); }

    std::vector<std::string> keys_with_prefix(const std::string& prefix);
};

#endif  // MINIREDIS_INCLUDE_DATABASE_H_
