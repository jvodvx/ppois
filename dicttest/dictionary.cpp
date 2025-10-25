#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <utility>

EnglishRussianDictionary::Node::Node(const char* eng, const char* rus)
    : english(eng), russian(rus), left(nullptr), right(nullptr), parent(nullptr), isRed(true) {
}

EnglishRussianDictionary::Node::Node(const std::string& eng, const std::string& rus)
    : english(eng), russian(rus), left(nullptr), right(nullptr), parent(nullptr), isRed(true) {
}

EnglishRussianDictionary::EnglishRussianDictionary() : root(nullptr), size(0) {}

EnglishRussianDictionary::~EnglishRussianDictionary() {
    clear(root);
}

void EnglishRussianDictionary::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void EnglishRussianDictionary::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left)
        rightChild->left->parent = node;
    rightChild->parent = node->parent;
    if (!node->parent)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;
    rightChild->left = node;
    node->parent = rightChild;
}

void EnglishRussianDictionary::rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right)
        leftChild->right->parent = node;
    leftChild->parent = node->parent;
    if (!node->parent)
        root = leftChild;
    else if (node == node->parent->right)
        node->parent->right = leftChild;
    else
        node->parent->left = leftChild;
    leftChild->right = node;
    node->parent = leftChild;
}

void EnglishRussianDictionary::fixInsert(Node* node) {
    while (node != root && node->parent && node->parent->isRed) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            if (uncle && uncle->isRed) {
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                if (node->parent) {
                    node->parent->isRed = false;
                    if (node->parent->parent) {
                        node->parent->parent->isRed = true;
                        rotateRight(node->parent->parent);
                    }
                }
            }
        }
        else {
            Node* uncle = node->parent->parent->left;
            if (uncle && uncle->isRed) {
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                if (node->parent) {
                    node->parent->isRed = false;
                    if (node->parent->parent) {
                        node->parent->parent->isRed = true;
                        rotateLeft(node->parent->parent);
                    }
                }
            }
        }
    }
    root->isRed = false;
}

void EnglishRussianDictionary::transplant(Node* u, Node* v) {
    if (!u->parent)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

EnglishRussianDictionary::Node* EnglishRussianDictionary::minimum(Node* node) const {
    if (!node) return nullptr;
    while (node->left)
        node = node->left;
    return node;
}

void EnglishRussianDictionary::fixDelete(Node* node) {
    while (node != root && node && !node->isRed) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;
            if (sibling && sibling->isRed) {
                sibling->isRed = false;
                node->parent->isRed = true;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }
            if (sibling &&
                (!sibling->left || !sibling->left->isRed) &&
                (!sibling->right || !sibling->right->isRed)) {
                if (sibling) sibling->isRed = true;
                node = node->parent;
            }
            else {
                if (sibling && sibling->right && !sibling->right->isRed) {
                    if (sibling->left) sibling->left->isRed = false;
                    sibling->isRed = true;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                if (sibling) {
                    sibling->isRed = node->parent->isRed;
                    if (sibling->right) sibling->right->isRed = false;
                }
                node->parent->isRed = false;
                rotateLeft(node->parent);
                node = root;
            }
        }
        else {
            Node* sibling = node->parent->left;
            if (sibling && sibling->isRed) {
                sibling->isRed = false;
                node->parent->isRed = true;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }
            if (sibling &&
                (!sibling->right || !sibling->right->isRed) &&
                (!sibling->left || !sibling->left->isRed)) {
                if (sibling) sibling->isRed = true;
                node = node->parent;
            }
            else {
                if (sibling && sibling->left && !sibling->left->isRed) {
                    if (sibling->right) sibling->right->isRed = false;
                    sibling->isRed = true;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                if (sibling) {
                    sibling->isRed = node->parent->isRed;
                    if (sibling->left) sibling->left->isRed = false;
                }
                node->parent->isRed = false;
                rotateRight(node->parent);
                node = root;
            }
        }
    }
    if (node) node->isRed = false;
}

EnglishRussianDictionary::Node* EnglishRussianDictionary::find(Node* node, const std::string& key) const {
    if (!node || node->english == key)
        return node;
    if (key < node->english)
        return find(node->left, key);
    return find(node->right, key);
}

EnglishRussianDictionary& EnglishRussianDictionary::operator+=(const std::pair<const char*, const char*>& words) {
    return *this += std::make_pair(std::string(words.first), std::string(words.second));
}

EnglishRussianDictionary& EnglishRussianDictionary::operator+=(const std::pair<std::string, std::string>& words) {
    // Проверяем, существует ли уже такое слово
    Node* existing = find(root, words.first);
    if (existing) {
        existing->russian = words.second;
        return *this;
    }

    Node* newNode = new Node(words.first, words.second);
    Node* current = root;
    Node* parent = nullptr;

    while (current) {
        parent = current;
        if (newNode->english < current->english)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;
    if (!parent)
        root = newNode;
    else if (newNode->english < parent->english)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsert(newNode);
    size++;
    return *this;
}

EnglishRussianDictionary& EnglishRussianDictionary::operator-=(const char* english) {
    return *this -= std::string(english);
}

EnglishRussianDictionary& EnglishRussianDictionary::operator-=(const std::string& english) {
    Node* z = find(root, english);
    if (!z) return *this;

    Node* y = z;
    Node* x;
    bool yOriginalColor = y->isRed;

    if (!z->left) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (!z->right) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        yOriginalColor = y->isRed;
        x = y->right;
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left) y->left->parent = y;
        y->isRed = z->isRed;
    }

    delete z;
    size--;

    if (!yOriginalColor && x)
        fixDelete(x);
    return *this;
}

std::string EnglishRussianDictionary::operator[](const char* english) const {
    return (*this)[std::string(english)];
}

std::string EnglishRussianDictionary::operator[](const std::string& english) const {
    Node* node = find(root, english);
    if (!node) return "";
    return node->russian;
}

std::string& EnglishRussianDictionary::operator[](const char* english) {
    return (*this)[std::string(english)];
}

std::string& EnglishRussianDictionary::operator[](const std::string& english) {
    Node* node = find(root, english);
    if (!node) {
        *this += std::make_pair(english, "");
        node = find(root, english);
    }
    return node->russian;
}

size_t EnglishRussianDictionary::count() const {
    return size;
}

bool EnglishRussianDictionary::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    clear(root);
    root = nullptr;
    size = 0;

    std::string eng, rus;
    while (std::getline(file, eng) && std::getline(file, rus)) {
        *this += std::make_pair(eng, rus);
    }

    file.close();
    return true;
}