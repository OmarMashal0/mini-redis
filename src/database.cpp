#include "database.h"

void Database::insert(const std::string& key, const std::string& value) {
    store_.insert(key, value);
    trie_.insert(key);
}

std::string Database::retrieve(const std::string& key) {
    return store_.retrieve(key);
}

void Database::remove(const std::string& key) {
    store_.remove(key);
    trie_.remove(key);
}

double Database::load_factor() const {
    return store_.load_factor();
}

std::vector<std::string> Database::keys_with_prefix(const std::string& prefix) {
    return trie_.starts_with(prefix);
}
