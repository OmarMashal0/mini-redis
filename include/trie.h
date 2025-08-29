#ifndef MINIREDIS_INCLUDE_TRIE_H_
#define MINIREDIS_INCLUDE_TRIE_H_

#include <string>
#include <unordered_map>
#include <vector>

class TrieNode {
public:
    bool is_end;
    std::unordered_map<char, TrieNode*> children;

    TrieNode() : is_end(false) {}
};

class Trie {
private:
    TrieNode* root;

    void collect_keys(TrieNode* node, const std::string& prefix, std::vector<std::string>& results) const;
    void free_node(TrieNode* node);
    bool remove_helper(TrieNode* node, const std::string& key, size_t depth);

public:
    Trie();
    ~Trie();

    void insert(const std::string& key);
    bool search(const std::string& key) const;
    std::vector<std::string> starts_with(const std::string& prefix) const;
    bool remove(const std::string& key);
};

#endif  // MINIREDIS_INCLUDE_TRIE_H_
