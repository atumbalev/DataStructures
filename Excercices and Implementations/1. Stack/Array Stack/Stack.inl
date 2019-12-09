#include "Stack.h"

template<typename T>
Stack<T>::Stack() : m_size(0), m_capacity(16)
{
    m_data = new T[m_capacity];
}

template<typename T>
Stack<T>::~Stack()
{
    delete [] m_data;
}

template<typename T>
void Stack<T>::push(const T &val)
{
    if (full())
    {
        resize();
    }
    m_data[m_size++] = val;
}

template<typename T>
T &Stack<T>::pop()
{
    return m_data[--m_size];
}

template<typename T>
T &Stack<T>::top() const
{
    return m_data[m_size -1];
}

template<typename T>
bool Stack<T>::empty() const
{
    return m_size == 0;
}

template<typename T>
bool Stack<T>::full() const
{
    return m_size == m_capacity -1;
}

template<typename T>
void Stack<T>::resize()
{
    T* newData = new T[m_capacity*2];

    for (int i = 0; i < m_size; ++i)
    {
        newData[i] = m_data[i];
    }

    delete [] m_data;
    m_capacity *= 2;
    m_data = newData;
}