#include <iostream>

#include "BinaryHeap.hpp"

int main(int argc, char* argv[]) {

    BinaryHeap<int> heap;

    heap.add(1);
    heap.add(3);
    heap.add(5);
    heap.add(8);
    heap.print();

    return 0;
}