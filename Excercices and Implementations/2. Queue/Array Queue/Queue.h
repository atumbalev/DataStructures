#pragma once

#include <iostream>

typedef int T;

class Queue
{
public:
    Queue();
    ~Queue();

    void enqueue(const T& elem);

    void dequeue();

    T front();

    bool empty() const;
    size_t size() const;

    void printQueue() const
    {
        size_t it = first;

        for (size_t i = 0; i < size(); ++i)
        {
            std::cout << m_data[it] << '_';
            it = getNext(it);
        }


    }

private:
    size_t getNext(size_t index) const;

    bool full() const;
    void resize();

    T *m_data;
    size_t m_capacity;
    size_t first, last;
};