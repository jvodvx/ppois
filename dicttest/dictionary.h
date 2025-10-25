#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <fstream>

class EnglishRussianDictionary {
private:
    struct Node {
        std::string english;
        std::string russian;
        Node* left;
        Node* right;
        Node* parent;
        bool isRed;

        Node(const char* eng, const char* rus);
        Node(const std::string& eng, const std::string& rus);
    };

    Node* root;
    size_t size;

    // Вспомогательные методы для красно-черного дерева
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void fixInsert(Node* node);
    void fixDelete(Node* node);
    void transplant(Node* u, Node* v);
    Node* minimum(Node* node) const;
    Node* find(Node* node, const std::string& key) const;
    void clear(Node* node);

public:
    EnglishRussianDictionary();
    ~EnglishRussianDictionary();

    EnglishRussianDictionary& operator+=(const std::pair<const char*, const char*>& words);
    EnglishRussianDictionary& operator+=(const std::pair<std::string, std::string>& words);
    EnglishRussianDictionary& operator-=(const char* english);
    EnglishRussianDictionary& operator-=(const std::string& english);
    std::string operator[](const char* english) const;
    std::string operator[](const std::string& english) const;
    std::string& operator[](const char* english);
    std::string& operator[](const std::string& english);

    size_t count() const;
    bool load(const std::string& filename);
};

#endif