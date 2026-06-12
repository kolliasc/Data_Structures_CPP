#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

class HashTable {
public:
    HashTable();
    ~HashTable();

    void buildFromFile(const std::string& filename);
    void insert(int key);
    bool search(int key) const;
    int getSize() const;
    std::string toString() const;

private:
    struct Node {
        int key;
        Node* next;
    };

    Node** table;
    int capacity;
    int size;

    int hashFunction(int key) const;
    void clearTable();
};

#endif
