#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

typedef char Type;

class Stack {
public:
    explicit Stack(size_t _size = 100);
    Stack& operator=(const Stack& other);
    ~Stack();

    bool Empty() const;
    bool Full() const;

    void Push(Type a);
    Type Pop();
private:
    Type *data;
    size_t tos;
    size_t size;
};

