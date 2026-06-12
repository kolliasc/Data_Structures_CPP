#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdexcept>
#include <string>

class MinHeap {
private:
    int* heap;
    int capacity;
    int size;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    MinHeap(int cap = 10);
    ~MinHeap();
    void insert(int number);
    int findMin();
    void deleteMin();
    int getSize();
    void buildFromFile(const std::string& filename);
    std::string toString() const;
};

#endif