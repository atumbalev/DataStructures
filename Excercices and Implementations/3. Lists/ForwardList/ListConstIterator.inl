#include "ListConstIterator.hpp"

template <typename T>
ListConstIterator<T>::ListConstIterator (std::nullptr_t) : it (nullptr)
{
}

template <typename T>
ListConstIterator<T>::ListConstIterator (const ListNode<T>* node) : it (node)
{
}

template <typename T>
ListConstIterator<T>::ListConstIterator (ListIterator<T> rhs) : it (rhs.it)
{
}

template <typename T>
const T& ListConstIterator<T>::operator* () const
{
    return it->data;
}

template <typename T>
const T* ListConstIterator<T>::operator-> () const
{
    return &(operator* ());
}

template <typename T>
ListConstIterator<T>& ListConstIterator<T>::operator++ ()
{
    it = it->next;
    return (*this);
}

template <typename T>
ListConstIterator<T> ListConstIterator<T>::operator++ (int)
{
    ListConstIterator res (*this);
    ++(*this);
    return res;
}
