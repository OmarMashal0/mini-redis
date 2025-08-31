#ifndef MINIREDIS_INCLUDE_DATABASE_H_
#define MINIREDIS_INCLUDE_DATABASE_H_

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "hash_table.h"
#include "trie.h"
#include "lru_cache.h"

class Database {
private:
    HashTable store_; // main key-value storage
    Trie trie_; // for prefix searches
    LRUCache cache_; // hot data cache
    std::map<std::string, bool> rb_tree_; // ordered keys for range queries
    std::ofstream log_file_; // persistence and recovery

public:
    explicit Database(size_t cacheCapacity = 5);
    ~Database();

    void insert(const std::string& key, const std::string& value);
    std::string retrieve(const std::string& key);
    void remove(const std::string& key);

    std::vector<std::string> keysWithPrefix(const std::string& prefix);
    std::vector<std::string> rangeQuery(const std::string& start, const std::string& end);
    bool exists(const std::string& key) const;
    std::vector<std::string> keys(const std::string& pattern = "*");
    
    void flushAll();
    void replayLog();
};

#endif  // MINIREDIS_INCLUDE_DATABASE_H_
