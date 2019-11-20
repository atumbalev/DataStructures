#include "Queue.h"

Queue::Queue() : m_capacity(2), first(0), last(0)
{
    m_data = new T[m_capacity];
}

Queue::~Queue()
{delete [] m_data; }

size_t Queue::getNext(size_t index) const
{
    return (index +1) % m_capacity;
}

void Queue::resize()
{
    T* newData = new T[m_capacity * 2];

    for (int i = 0; i < size(); ++i)
    {
        newData[i] = m_data[first];
        first = getNext(first);
    }

    m_capacity *= 2;
    first = 0;
    last = size();
}

bool Queue::full() const
{
    return first == getNext(last);
}

size_t Queue::size() const
{
//        Modulus on negative numbers is ambiguous
    return (last - first + m_capacity) % m_capacity;
}

bool Queue::empty() const
{
    return first == last;
}

void Queue::enqueue(const T &elem)
{
    if(full())
    {
        resize();
    }

    m_data[last] = elem;
    last = getNext(last);
}

void Queue::dequeue()
{
    first = getNext(first);
}

T Queue::front()
{
    return m_data[first];
}
