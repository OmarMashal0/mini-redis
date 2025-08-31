#ifndef MINIREDIS_INCLUDE_LRU_CACHE_H_
#define MINIREDIS_INCLUDE_LRU_CACHE_H_

#include <unordered_map>
#include <string>

struct LRUNode {
    std::string key;
    std::string value;
    LRUNode* prev;
    LRUNode* next;

    LRUNode(const std::string& k, const std::string& v)
        : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    size_t capacity_;
    std::unordered_map<std::string, LRUNode*> map_;
    LRUNode* head; // dummy head node
    LRUNode* tail; // dummy tail node

    void moveToFront(LRUNode* node);
    void removeNode(LRUNode* node);
    void addToFront(LRUNode* node);

public:
    explicit LRUCache(size_t capacity);
    ~LRUCache();

    std::string get(const std::string& key);
    void put(const std::string& key, const std::string& value);
    void erase(const std::string& key);
    size_t capacity() const { return capacity_; }
};

#endif  // MINIREDIS_INCLUDE_LRU_CACHE_H_
