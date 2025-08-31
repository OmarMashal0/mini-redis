#include "lru_cache.h"

LRUCache::LRUCache(size_t capacity) : capacity_(capacity) {
    // create dummy head and tail nodes for easier list manipulation
    head = new LRUNode("", "");
    tail = new LRUNode("", "");
    head->next = tail;
    tail->prev = head;
}

LRUCache::~LRUCache() {
    LRUNode* curr = head;
    while (curr) {
        LRUNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

void LRUCache::removeNode(LRUNode* node) {
    // remove node from its current position in the list
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::addToFront(LRUNode* node) {
    // add node right after dummy head (most recently used)
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

void LRUCache::moveToFront(LRUNode* node) {
    // move existing node to front when accessed
    removeNode(node);
    addToFront(node);
}

std::string LRUCache::get(const std::string& key) {
    if (map_.find(key) == map_.end()) {
        return "";
    }
    LRUNode* node = map_[key];
    moveToFront(node);
    return node->value;
}

void LRUCache::put(const std::string& key, const std::string& value) {
    if (map_.find(key) != map_.end()) {
        // update existing key and move to front
        LRUNode* node = map_[key];
        node->value = value;
        moveToFront(node);
    } else {
        if (map_.size() == capacity_) {
            // remove least recently used node (before dummy tail)
            LRUNode* lru = tail->prev;
            map_.erase(lru->key);
            removeNode(lru);
            delete lru;
        }
        LRUNode* newNode = new LRUNode(key, value);
        map_[key] = newNode;
        addToFront(newNode);
    }
}

void LRUCache::erase(const std::string& key) {
    auto it = map_.find(key);
    if (it == map_.end()) return;

    LRUNode* node = it->second;
    removeNode(node);
    map_.erase(it);
    delete node;
}
