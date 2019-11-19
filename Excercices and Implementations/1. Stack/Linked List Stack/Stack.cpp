#include "Stack.h"

Stack::~Stack()
{
    while (tos)
    {
        Node* tmp = tos;
        tos = tos->next;
        delete tmp;
    }
}

bool Stack::push(const T &elem)
{
    if (full())
        return false;

    spare->data = elem;
    spare->next = tos;
    tos = spare;

    spare = new (std::nothrow) Node;

    return full();
}

T Stack::pop()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty!");
    }

    T ret = tos->data;
    Node* tmp = tos;
    tos = tos->next;
    delete tmp;
    return ret;
}

bool Stack::empty() const
{
    return !tos;
}

bool Stack::full() const
{
    if (!spare)
    {
        spare = new (std::nothrow) Node;
    }

    return !spare;
}
