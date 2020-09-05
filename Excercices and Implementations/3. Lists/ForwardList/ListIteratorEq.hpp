#pragma once

#include "ListIterator.hpp"
#include "ListConstIterator.hpp"

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
bool operator== (ListConstIterator<T> lhs, ListIterator<T> rhs)
{
    return lhs == ListConstIterator<T> (rhs);
}

template <typename T>
bool operator== (ListIterator<T> lhs, ListConstIterator<T> rhs)
{
    return rhs == lhs;
}

template <typename T>
bool operator== (ListIterator<T> lhs, ListIterator<T> rhs)
{
    return ListConstIterator<T> (lhs) == ListConstIterator<T> (rhs);
}

template <typename T>
bool operator== (ListConstIterator<T> lhs, std::nullptr_t)
{
    return lhs == ListConstIterator<T> (nullptr);
}

template <typename T>
bool operator== (ListIterator<T> lhs, std::nullptr_t)
{
    return ListConstIterator<T> (lhs) == ListConstIterator<T> (nullptr);
}

template <typename T>
bool operator!= (ListConstIterator<T> lhs, ListConstIterator<T> rhs)
{
    return !(lhs==rhs);
}

template <typename T>
bool operator!= (ListConstIterator<T> lhs, ListIterator<T> rhs)
{
    return !(lhs==rhs);
}

template <typename T>
bool operator!= (ListIterator<T> lhs, ListConstIterator<T> rhs)
{
    return !(lhs==rhs);
}

template <typename T>
bool operator!= (ListIterator<T> lhs, ListIterator<T> rhs)
{
    return !(lhs==rhs);
}

template <typename T>
bool operator!= (ListConstIterator<T> lhs, std::nullptr_t)
{
    return !(lhs==nullptr);
}

template <typename T>
bool operator!= (ListIterator<T> lhs, std::nullptr_t)
{
    return !(lhs==nullptr);
}
