#ifndef FORWARD_LIST_CONST_ITERATOR_INCLUDED
#define FORWARD_LIST_CONST_ITERATOR_INCLUDED

#include <iterator>

#include "List.hpp"

template <typename T>
class ForwardList;

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator : public std::iterator<std::forward_iterator_tag, T>
{
    friend class ForwardList<T>;

    friend bool operator== (ListConstIterator<T> lhs, ListConstIterator<T> rhs)
    {
        return lhs.it == rhs.it;
    }

public:
    ListConstIterator () = default;
    ListConstIterator (std::nullptr_t);
    ListConstIterator (ListIterator<T> it);

    ListConstIterator (const ListConstIterator& rhs) = default;
    ListConstIterator& operator= (const ListConstIterator& rhs) = default;

    const T& operator* () const;
    const T* operator-> () const;

    ListConstIterator& operator++ ();
    ListConstIterator operator++ (int);

private:
    ListConstIterator (const ListNode<T>* node);

private:
    const ListNode<T>* it;
};

#include "ListIteratorEq.hpp"
#include "ListConstIterator.inl"

#endif /* FORWARD_LIST_ITERATOR_INCLUDED */
