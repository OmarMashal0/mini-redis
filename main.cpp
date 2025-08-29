#include <iostream>
#include "database.h"

int main() {
    Database db(2); // cache size = 2

    // Insert keys
    db.insert("user:1", "Alice");
    db.insert("user:2", "Bob");

    // Retrieve (loads into cache)
    std::cout << "GET user:1 -> " << db.retrieve("user:1") << std::endl;
    std::cout << "GET user:2 -> " << db.retrieve("user:2") << std::endl;

    // Insert new key -> cache full, will evict least recently used
    db.insert("user:3", "Charlie");

    // Test cache behavior
    std::cout << "GET user:3 -> " << db.retrieve("user:3") << std::endl;
    std::cout << "GET user:1 -> " << db.retrieve("user:1") << std::endl;
    std::cout << "GET user:2 -> " << db.retrieve("user:2") << std::endl; // might be evicted

    // Prefix search test
    std::cout << "Keys with prefix 'user:' -> ";
    auto results = db.keys_with_prefix("user:");
    for (auto& key : results) std::cout << key << " ";
    std::cout << std::endl;

    // Removal test
    db.remove("user:1");
    std::cout << "Keys with prefix 'user:' after removing user:1 -> ";
    auto results2 = db.keys_with_prefix("user:");
    for (auto& key : results2) std::cout << key << " ";
    std::cout << std::endl;

    return 0;
}
