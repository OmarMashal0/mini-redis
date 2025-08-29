#ifndef MINIREDIS_INCLUDE_LRU_CACHE_H_
#define MINIREDIS_INCLUDE_LRU_CACHE_H_

#include <unordered_map>
#include <string>

// Doubly Linked List Node
struct LRUNode {
    std::string key;
    std::string value;
    LRUNode* prev;
    LRUNode* next;

    LRUNode(const std::string& k, const std::string& v)
        : key(k), value(v), prev(nullptr), next(nullptr) {
    }
};

class LRUCache {
private:
    size_t capacity_;
    std::unordered_map<std::string, LRUNode*> map_;
    LRUNode* head;  // dummy head
    LRUNode* tail;  // dummy tail

    void move_to_front(LRUNode* node);
    void remove_node(LRUNode* node);
    void add_to_front(LRUNode* node);

public:
    explicit LRUCache(size_t capacity);
    ~LRUCache();

    std::string get(const std::string& key);
    void put(const std::string& key, const std::string& value);
};

#endif  // MINIREDIS_INCLUDE_LRU_CACHE_H_
