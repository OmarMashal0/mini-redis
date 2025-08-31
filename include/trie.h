#ifndef MINIREDIS_INCLUDE_TRIE_H_
#define MINIREDIS_INCLUDE_TRIE_H_

#include <string>
#include <unordered_map>
#include <vector>

class TrieNode {
public:
    bool isEnd; // marks end of a complete key
    std::unordered_map<char, TrieNode*> children; // character to child node mapping

    TrieNode() : isEnd(false) {}
};

class Trie {
private:
    TrieNode* root;

    void collectKeys(TrieNode* node, const std::string& prefix, std::vector<std::string>& results) const;
    void freeNode(TrieNode* node);
    bool removeHelper(TrieNode* node, const std::string& key, size_t depth);

public:
    Trie();
    ~Trie();

    void insert(const std::string& key);
    std::vector<std::string> startsWith(const std::string& prefix) const;
    bool remove(const std::string& key);
};

#endif  // MINIREDIS_INCLUDE_TRIE_H_
