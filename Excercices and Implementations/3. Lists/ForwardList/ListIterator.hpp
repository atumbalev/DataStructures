#ifndef FORWARD_LIST_ITERATOR_INCLUDED
#define FORWARD_LIST_ITERATOR_INCLUDED

#include <iterator>
#include "List.hpp"

template <typename T>
class List;

template <typename T>
class ListConstIterator;

template <typename T>
class ListIterator : public std::iterator<std::forward_iterator_tag, T>
{
    friend class List<T>;
    friend class ListConstIterator<T>;

public:
    ListIterator () = default;
    ListIterator (std::nullptr_t);

    ListIterator (const ListIterator& rhs) = default;
    ListIterator& operator= (const ListIterator& rhs) = default;

    T& operator* ();
    const T& operator* () const;

    T* operator-> ();
    const T* operator-> () const;

    ListIterator& operator++ ();
    ListIterator operator++ (int);

private:
    ListIterator (ListNode<T>* node);

private:
    ListNode<T>* it;
};

#include "ListIteratorEq.hpp"
#include "ListIterator.inl"

#endif /* FORWARD_LIST_ITERATOR_INCLUDED */
