#include <stdexcept>
#include "Stack.h"

Stack::Stack(size_t _size) : size(_size), tos(0)
{
    data = new Type[size];
}

Stack::~Stack()
{
    delete [] data;
}

Stack& Stack::operator=(const Stack &other)
        {

    Type* newData = new Type[other.size];

    for (int i = 0; i < other.tos; ++i)
    {
        newData[i] = other.data[i];
    }

    tos = other.tos;
    size = other.size;
    data = newData;

    return *this;
}

bool Stack::empty() const
{
    return tos == 0;
}

bool Stack::full() const
{
    return tos == size -1;
}

void Stack::push(Type a)
{
    if(full())
    {
        throw std::overflow_error("Stack is full");
    }
    data[tos++] = a;
}

Type Stack::pop()
{   if(empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    return data[--tos];
}

Type Stack::top()
{
    return data[tos];
}
