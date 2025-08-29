#include "database.h"

void Database::insert(const std::string& key, const std::string& value) {
    store_.insert(key, value);
    trie_.insert(key);
    cache_.put(key, value);
}

std::string Database::retrieve(const std::string& key) {
    // check cache first
    std::string cached = cache_.get(key);
    if (!cached.empty()) {
        return cached;
    }
    // fallback to hash table
    std::string value = store_.retrieve(key);
    if (!value.empty()) {
        cache_.put(key, value); // keep cache hot
    }
    return value;
}

void Database::remove(const std::string& key) {
    store_.remove(key);
    trie_.remove(key);
    // cache does not need explicit removal, it will naturally evict if unused
}

double Database::load_factor() const {
    return store_.load_factor();
}

std::vector<std::string> Database::keys_with_prefix(const std::string& prefix) {
    return trie_.starts_with(prefix);
}
