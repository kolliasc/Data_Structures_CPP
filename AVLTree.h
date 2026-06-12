#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int size;

    Node* insert(Node* node, int key);
    Node* deleteNode(Node* root, int key);
    Node* minValueNode(Node* node);
    int height(Node* node);
    int getBalance(Node* node);
    Node* leftRotate(Node* x);
    Node* rightRotate(Node* y);
    void inOrder(Node* root, std::ostream& os);
    bool search(Node* root, int key) const;

public:
    AVLTree();
    ~AVLTree();
    void insert(int key);
    bool search(int key) const;
    void deleteKey(int key);
    int findMin() const;
    int getSize() const;
    void buildFromFile(const std::string& filename);
    std::string toString();
    void clear(Node* node);
};

#endif // AVLTREE_H