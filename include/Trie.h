#ifndef TRIE_H
#define TRIE_H

#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#define LIMIT 5

class TrieNode {
public:
    TrieNode();

    bool endMark;
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
};

class Trie {
public:
    Trie();
    ~Trie();

    void Insert(const std::string& word);
    std::vector<std::string> SearchSuggestions(const std::string& prefix);

private:
    std::unique_ptr<TrieNode> root;

    void DFS(TrieNode* node, std::string currentWord, std::vector<std::string>& results);
};

#endif