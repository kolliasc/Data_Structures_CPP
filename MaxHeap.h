#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdexcept>
#include <string>

class MaxHeap {
private:
    int* heap;
    int capacity;
    int size;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    MaxHeap(int cap = 10);
    ~MaxHeap();
    void insert(int number);
    int findMax();
    void deleteMax();
    int getSize();
    void buildFromFile(const std::string& filename);
    std::string toString();
};

#endif // MAXHEAP_H

#endif // MAXHEAP_H