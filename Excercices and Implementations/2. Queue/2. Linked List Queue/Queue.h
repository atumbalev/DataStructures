#pragma once

#include <iostream>
#include "Node.h"

class Queue
{
public:
    Queue();
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    ~Queue();

    void enqueue(T a);
    T dequeue();
    T& front();

    size_t size() const;
    bool empty() const;
private:
    void copy(const Node*);
    void del(const Node*);

    Node *begin, *end;
    size_t count;
};