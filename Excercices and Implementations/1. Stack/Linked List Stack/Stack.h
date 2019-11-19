#pragma once

#include <new>
#include <stdexcept>

//typedef instead of template because implementation is shorter
typedef int T;

struct Node
{
   T data;
   Node* next;
};

class Stack
{
public:
    Stack() : tos(nullptr), spare(nullptr) {}
    ~Stack();

    //@return true if next add will succeed
    //@return false if next add will fail or if this add has failed
    bool push(const T& elem);
    //@returns the top of the stack
    T pop();

    //@return true if tos is nullptr
    bool empty() const;
    //@return true if next allocation of memory will fail
    bool full() const;
private:
    Node* tos;
    mutable Node* spare;
};