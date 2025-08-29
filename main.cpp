#include <iostream>
#include "database.h"

int main() {
    Database db;

    // Insert some keys
    db.insert("user:1", "Alice");
    db.insert("user:2", "Bob");
    db.insert("order:1", "Laptop");

    // Retrieve single key
    std::cout << "GET user:1 -> " << db.retrieve("user:1") << std::endl;

    // Prefix search before removal
    std::cout << "Prefix search 'user:' before removal -> ";
    auto results1 = db.keys_with_prefix("user:");
    for (auto& key : results1) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    // Remove one key
    db.remove("user:1");

    // Prefix search after removal
    std::cout << "Prefix search 'user:' after removal -> ";
    auto results2 = db.keys_with_prefix("user:");
    for (auto& key : results2) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    return 0;
}
