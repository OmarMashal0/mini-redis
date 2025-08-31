#include "database.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

Database::Database(size_t cacheCapacity) : cache_(cacheCapacity) {
    log_file_.open("db.log", std::ios::app);
    if (log_file_.is_open()) {
        replayLog();
    }
}

Database::~Database() {
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

void Database::insert(const std::string& key, const std::string& value) {
    store_.insert(key, value);
    trie_.insert(key);
    cache_.put(key, value);
    rb_tree_[key] = true;
    
    if (log_file_.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        
        log_file_ << "[" << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S") << "] ";
        log_file_ << "SET " << key << " " << value << std::endl;
        log_file_.flush();
    }
}

std::string Database::retrieve(const std::string& key) {
    std::string cached = cache_.get(key);
    if (!cached.empty()) return cached;

    std::string value = store_.retrieve(key);
    if (!value.empty()) cache_.put(key, value);
    return value;
}

void Database::remove(const std::string& key) {
    store_.remove(key);
    trie_.remove(key);
    rb_tree_.erase(key);
    cache_.erase(key);
    
    if (log_file_.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        
        log_file_ << "[" << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S") << "] ";
        log_file_ << "DEL " << key << std::endl;
        log_file_.flush();
    }
}

std::vector<std::string> Database::keysWithPrefix(const std::string& prefix) {
    return trie_.startsWith(prefix);
}

std::vector<std::string> Database::rangeQuery(const std::string& start, const std::string& end) {
    std::vector<std::string> result;
    for (auto it = rb_tree_.lower_bound(start); it != rb_tree_.end() && it->first <= end; ++it) {
        result.push_back(it->first);
    }
    return result;
}

bool Database::exists(const std::string& key) const {
    return !store_.retrieve(key).empty();
}

std::vector<std::string> Database::keys(const std::string& pattern) {
    if (pattern == "*") {
        std::vector<std::string> all_keys;
        for (const auto& pair : rb_tree_) {
            all_keys.push_back(pair.first);
        }
        return all_keys;
    }
    
    if (pattern.length() > 1 && pattern.back() == '*') {
        std::string prefix = pattern.substr(0, pattern.length() - 1);
        return keysWithPrefix(prefix);
    }
    
    if (exists(pattern)) {
        return {pattern};
    }
    
    return {};
}

void Database::flushAll() {
    store_ = HashTable();
    trie_ = Trie();
    cache_ = LRUCache(cache_.capacity());
    rb_tree_.clear();
    
    log_file_.close();
    log_file_.open("db.log", std::ios::trunc);
}

void Database::replayLog() {
    std::ifstream log_read("db.log");
    if (!log_read.is_open()) return;
    
    std::string line;
    while (std::getline(log_read, line)) {
        size_t timestamp_end = line.find("] ");
        if (timestamp_end == std::string::npos) continue;
        
        std::string command_part = line.substr(timestamp_end + 2);
        
        std::istringstream iss(command_part);
        std::string operation, key, value;
        
        iss >> operation >> key;
        if (operation.empty() || key.empty()) continue;
        
        std::getline(iss, value);
        if (!value.empty() && value[0] == ' ') {
            value = value.substr(1);
        }
        
        if (operation == "SET" && !value.empty()) {
            store_.insert(key, value);
            trie_.insert(key);
            rb_tree_[key] = true;
            cache_.put(key, value);
        } else if (operation == "DEL") {
            store_.remove(key);
            trie_.remove(key);
            rb_tree_.erase(key);
            cache_.erase(key);
        }
    }
    
    log_read.close();
}
