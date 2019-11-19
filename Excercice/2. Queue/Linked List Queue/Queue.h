#pragma once

#include <iostream>
#include "Node.h"

typedef int T;

class Queue
{
public:
    Queue();
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    ~Queue();

    bool empty() const;
    void enqueue(T a);
    T& dequeue();
    size_t size() const;
private:
    void copy(const Node*);
    void del(const Node*);

    Node *begin, *end;
    size_t count;
};