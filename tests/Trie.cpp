#include "Trie.h"

TrieNode::TrieNode() : endMark(false) { }

Trie::Trie() : root(std::make_unique<TrieNode>()) { }

Trie::~Trie() {}

void Trie::Insert(const std::string &word) {
    TrieNode *curr = root.get();

    for (char ch : word) {
        if (!curr->children.count(ch)) {
            curr->children[ch] = std::make_unique<TrieNode>();
        }
        curr = curr->children[ch].get();
    }
    curr->endMark = true;
}

std::vector<std::string> Trie::SearchSuggestions(const std::string &prefix) {
    std::vector<std::string> results;
    TrieNode *curr = root.get();

    for (char ch : prefix) {
        if (!curr->children.count(ch)) {
            return results;
        }
        curr = curr->children[ch].get();
    }

    DFS(curr, prefix, results);
    return results;
}

void Trie::DFS(TrieNode *node, std::string currentWord, std::vector<std::string> &results) {
    if (results.size() >= LIMIT) 
        return;

    if (node->endMark) {
        results.push_back(currentWord);
        if (results.size() >= LIMIT)
            return; 
    }
    
    std::unordered_map<char, std::unique_ptr<TrieNode>>::iterator it;      
    for (it = node->children.begin(); it != node->children.end(); it++) {
        DFS(it->second.get(), currentWord + it->first, results);
    }
}