#include "trie.h"

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    freeNode(root);
}

void Trie::freeNode(TrieNode* node) {
    for (auto& child : node->children) {
        freeNode(child.second);
    }
    delete node;
}

void Trie::insert(const std::string& key) {
    TrieNode* node = root;
    for (char c : key) {
        if (!node->children[c]) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->isEnd = true;
}

void Trie::collectKeys(TrieNode* node, const std::string& prefix, std::vector<std::string>& results) const {
    if (node->isEnd) {
        results.push_back(prefix);
    }
    for (auto& pair : node->children) {
        collectKeys(pair.second, prefix + pair.first, results);
    }
}

std::vector<std::string> Trie::startsWith(const std::string& prefix) const {
    TrieNode* node = root;
    for (char c : prefix) {
        if (!node->children.count(c)) {
            return {};
        }
        node = node->children.at(c);
    }

    std::vector<std::string> results;
    collectKeys(node, prefix, results);
    return results;
}

bool Trie::remove(const std::string& key) {
    return removeHelper(root, key, 0);
}

bool Trie::removeHelper(TrieNode* node, const std::string& key, size_t depth) {
    if (!node) return false;

    if (depth == key.size()) {
        if (!node->isEnd) return false;
        node->isEnd = false;
        return node->children.empty();
    }

    char c = key[depth];
    if (!node->children.count(c)) return false;

    bool shouldDeleteChild = removeHelper(node->children[c], key, depth + 1);

    if (shouldDeleteChild) {
        delete node->children[c];
        node->children.erase(c);
        return node->children.empty() && !node->isEnd;
    }

    return false;
}
