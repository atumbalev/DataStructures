#ifndef FORWARD_LIST_INCLUDED
#define FORWARD_LIST_INCLUDED

#include <initializer_list>
#include <cassert>

#include "ListNode.hpp"
#include "ListIterator.hpp"
#include "ListConstIterator.hpp"

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
class ForwardList
{
public:
    using Iterator = ListIterator<T>;
    using ConstIterator = ListConstIterator<T>;

public:
    ForwardList () : m_size(0) {}

    ForwardList (std::initializer_list<T> list) : m_size(0)
    {
        for (auto elem : list)
        {
            pushFront(elem);
        }
    }

    ForwardList (const ForwardList& rhs);
    ForwardList (ForwardList&& rhs);

    ForwardList& operator= (const ForwardList& rhs);
    ForwardList& operator= (ForwardList&& rhs);

    ~ForwardList ()
    {
        erase();
    }

    Iterator beforeBegin ()
    {
        return Iterator(m_sentinel);
    }
    Iterator begin ()
    {
        return Iterator(m_sentinel->next);
    }
    Iterator end ()
    {
        return Iterator (nullptr);
    }

    ConstIterator cbeforeBegin () const
    {
        return ConstIterator(m_sentinel);
    }
    ConstIterator cbegin () const
    {
        return ConstIterator(m_sentinel->next);
    }
    ConstIterator cend () const
    {
        return ConstIterator(nullptr);
    }

    T& front ()
    {
        assert(!empty());
        return *begin();
    }
    const T& front () const
    {
        assert(!empty());
        return *cbegin();
    }
    bool empty () const
    {
        return m_size == 0;
    }
    size_t size () const
    {
        return m_size;
    }

    Iterator insertAfter (ConstIterator it, const T& value)
    {

    }

    Iterator pushFront (const T& value)
    {
        insertAfter(cbeforeBegin());
        return begin();
    }

    Iterator removeAfter (ConstIterator it)
    {
        ListNode<T>* beforeRemove = it.it;
        ListNode<T>* toRemove = beforeRemove->next;
        ListNode<T>* afterRemove = toRemove->next;

        beforeRemove->next = afterRemove;

        delete toRemove;

        return Iterator(afterRemove);
    }

    void popFront();


    void erase();
    void swap(ForwardList& rhs);

private:
    ListNode<T> m_sentinel;
    size_t m_size;
};

#include "List.inl"

#endif /* FORWARD_LIST_INCLUDED */
