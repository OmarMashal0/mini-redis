#include "lru_cache.h"

LRUCache::LRUCache(size_t capacity) : capacity_(capacity) {
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

void LRUCache::remove_node(LRUNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::add_to_front(LRUNode* node) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

void LRUCache::move_to_front(LRUNode* node) {
    remove_node(node);
    add_to_front(node);
}

std::string LRUCache::get(const std::string& key) {
    if (map_.find(key) == map_.end()) {
        return ""; // not found
    }
    LRUNode* node = map_[key];
    move_to_front(node);
    return node->value;
}

void LRUCache::put(const std::string& key, const std::string& value) {
    if (map_.find(key) != map_.end()) {
        // update existing
        LRUNode* node = map_[key];
        node->value = value;
        move_to_front(node);
    }
    else {
        // create new node
        if (map_.size() == capacity_) {
            // evict least recent (node before tail)
            LRUNode* lru = tail->prev;
            map_.erase(lru->key);
            remove_node(lru);
            delete lru;
        }
        LRUNode* new_node = new LRUNode(key, value);
        map_[key] = new_node;
        add_to_front(new_node);
    }
}
