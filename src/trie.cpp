#include "trie.h"

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    free_node(root);
}

void Trie::free_node(TrieNode* node) {
    for (auto& child : node->children) {
        free_node(child.second);
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
    node->is_end = true;
}

bool Trie::search(const std::string& key) const {
    TrieNode* node = root;
    for (char c : key) {
        if (!node->children.count(c)) {
            return false;
        }
        node = node->children.at(c);
    }
    return node->is_end;
}

void Trie::collect_keys(TrieNode* node, const std::string& prefix, std::vector<std::string>& results) const {
    if (node->is_end) {
        results.push_back(prefix);
    }
    for (auto& pair : node->children) {
        collect_keys(pair.second, prefix + pair.first, results);
    }
}

std::vector<std::string> Trie::starts_with(const std::string& prefix) const {
    TrieNode* node = root;
    for (char c : prefix) {
        if (!node->children.count(c)) {
            return {};
        }
        node = node->children.at(c);
    }

    std::vector<std::string> results;
    collect_keys(node, prefix, results);
    return results;
}

bool Trie::remove(const std::string& key) {
    return remove_helper(root, key, 0);
}

bool Trie::remove_helper(TrieNode* node, const std::string& key, size_t depth) {
    if (!node) return false;

    if (depth == key.size()) {
        if (!node->is_end) return false;  // key not found
        node->is_end = false;

        // if no children, this node can be deleted by parent
        return node->children.empty();
    }

    char c = key[depth];
    if (!node->children.count(c)) return false;

    bool should_delete_child = remove_helper(node->children[c], key, depth + 1);

    if (should_delete_child) {
        delete node->children[c];
        node->children.erase(c);

        // if this node has no other children and is not end of another key, signal delete
        return node->children.empty() && !node->is_end;
    }

    return false;
}
