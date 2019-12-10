#pragma once

#include <iostream>

template <typename T>
class BinaryHeap
{
public:
    BinaryHeap(): size(0), capacity(16), heapArray(new T[capacity]) {}

    ~BinaryHeap()
    {
        delete [] heapArray;
    }

    T& getMin()
    {
        return heapArray[0];
    }

    int getParent(int index)
    {
        return (index - 1) / 2;
    }

    int getLeftChild(int index)
    {
        return 2 * index + 1;
    }

    int getRightChild(int index)
    {
        return (2 * index + 2);
    }

    T& extractMin()
    {
        T& root = heapArray[0];
        --size;
        if (size)
        {
            heapArray[0] = heapArray[size];
            siftDown(0);
        }
        return root;
    }

    void add(const T& elem)
    {
        if (size == capacity)
        {
            resize();
        }
        heapArray[size++] = elem;
        siftUp(size -1);
    }

    void siftUp(int index)
    {

        T& head = heapArray[index];
        int i = index;
        while (i > 0)
        {
            int prev = getParent(i);
            if (heapArray[prev] > head)
            {
                heapArray[prev] = heapArray[i];
            }
            else
            {
                break;
            }
            i = prev;

        }
        heapArray[i] = head;
    }

    void siftDown(int index)
    {
        T& head = heapArray[index];
        int i = index;
        while (getLeftChild(i) < head)
        {
            int minChild = getLeftChild(i);
            int right = minChild + 1;
            if (minChild < size - 1 && heapArray[right] < heapArray[minChild])
            {
                minChild = right;
            }
            if (heapArray[minChild])
            {
                heapArray[i] = heapArray[minChild];
                i = minChild;
            }
            else
                break;
        }
        heapArray[i] = head;
    }

    const size_t& getSize() const
    {
        return size;
    }

    void print() const
    {


        for (int i = 0; i < size; ++i)
        {
            std::cout << heapArray[i] << std::endl;
        }
    }

    void swap(int i, int j)
    {
        std::swap(heapArray[i], heapArray[j]);
    }

private:

    void resize()
    {
        T* newData = new T[capacity * 2];

        for (int i = 0; i < size; ++i)
        {
            newData[i] = heapArray[i];
        }

        heapArray = newData;
        capacity *= 2;
    }
    size_t size;
    size_t capacity;
    T* heapArray;
};
