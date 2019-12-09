#pragma once

#include <iostream>

template <typename T>
class Stack
{
public:
    Stack();
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    ~Stack();

    void push(const T& val);
    T& pop();
    T& top() const;

    bool empty() const;
    bool full() const;

private:
    void resize();

    T* m_data;
    size_t m_size;
    size_t m_capacity;
};

#include "Stack.inl"