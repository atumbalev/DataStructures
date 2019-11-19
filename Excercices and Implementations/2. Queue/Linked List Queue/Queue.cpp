#include "Queue.h"

Queue::Queue()
{
    begin = end = nullptr;
    count = 0;
}

Queue::Queue(const Queue & other)
{
    copy(other.begin);
    count = other.size();
}

void Queue::copy(const Node * n)
{
    if (n == nullptr)
    {
        begin = end = nullptr;
    }

    Node * cur = new Node(n->data);
    begin = cur;

    while (n->next)
    {
        n = n->next;
        cur->next = new Node(n->data);
        cur = cur->next;
    }
    end = cur;

}

void Queue::del(const Node *n)
{
    if(n)
    {
        del(n->next);
        delete n;
    }

    begin = nullptr; //TODO
}

Queue &Queue::operator=(const Queue &other)
{
    if(this != &other)
    {
        del(begin);
        copy(other.begin);
        count = other.size();
    }
}

Queue::~Queue()
{
    del(begin);
    count = 0;
}

bool Queue::empty() const
{
    return begin == nullptr;
}

void Queue::enqueue(T a)
{
    Node* n = new Node(a);
    if (!empty())
    {
        end->next = n;
    }
    else
    {
        begin = n;
        end = n;
    }
    ++count;

}

T &Queue::dequeue()
{
    if(empty()) { throw std::out_of_range("Queue is empty"); }

    Node* tmp = begin;
    T ret = tmp->data;
    delete tmp;
    --count;

    begin = begin->next;
    return ret;

}

size_t Queue::size() const
{
    return count;
}

