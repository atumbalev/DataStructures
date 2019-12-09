#include "List.h"

template<typename T>
List<T>::List()
{
    dummy.prev = dummy.next = &dummy;
}

template<typename T>
List<T>::List(const List<T> &other)
{
    dummy.prev = dummy.next = &dummy;
    copy(other);
}

template<typename T>
List<T> &List<T>::operator=(const List<T> &other)
{
    if (this == &other) {
        return *this;
    }
    clear();
    copy(other);
    return *this;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
void List<T>::insertAfterNode(List::Node *node, const T &value)
{
    Node *newNode = new Node;
    newNode->data = value;

    // Attach node to new neighbours
    newNode->next = node->next;
    newNode->prev = node;

    // Attach neighbours to node
    node->next->prev = newNode;
    node->next = newNode;
    ++size;
}

template<typename T>
void List<T>::removeNode(List::Node *node)
{
    assert(node != &dummy);
    assert(size > 0);
    --size;
    // Attach prev and next to eachother
    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
}

template<typename T>
void List<T>::copy(const List<T> &other)
{
    assert(isEmpty());
    for (ConstIterator it = other.begin(); it != other.end(); ++it) {
        pushBack(*it);
    }
}

template<typename T>
void List<T>::clear()
{
    while (!isEmpty()) {
        popBack();
    }
}

template<typename T>
void List<T>::popBack()
{
    removeNode(dummy.prev);
}

template<typename T>
void List<T>::popFront()
{
    removeNode(dummy.next);
}

template<typename T>
void List<T>::pushFront(const T &value)
{
    insertAfterNode(&dummy, value);
}

template<typename T>
void List<T>::pushBack(const T &value)
{
    insertAfterNode(dummy.prev, value);
}

template<typename T>
void List<T>::insertAfter(const List::Iterator &it, const T &value)
{
    insertAfterNode(it.current, value);
}

template<typename T>
void List<T>::insertBefore(const List::Iterator &it, const T &value)
{
    insertAfterNode(it.current->prev, value);
}

template<typename T>
void List<T>::remove(const List::Iterator &it)
{
    removeNode(it.current);
}

template<typename T>
void List<T>::splice(List<T> &other, const List::Iterator &where)
{
    if (other.isEmpty()) {
        return;
    }

    Node *destination = where.current;
    Node *source = &other.dummy;

    // Attach elements from @other to our elements
    source->next->prev = destination;
    source->prev->next = destination->next;

    // Attach our elements to other's elements
    destination->next->prev = source->prev;
    destination->next = source->next;

    // Detach other's dummy from it's elements
    size += other.size;
    source->next = source->prev = source;
    other.size = 0;

    assert(other.isEmpty());
}

template<typename T>
void List<T>::splice(List<T> &other)
{
    Iterator it = end();
    splice(other, --it);
}

template<typename T>
bool List<T>::isEmpty() const
{
    const bool empty = dummy.prev == &dummy;
    assert(empty == (size == 0));
    return empty;
}

template<typename T>
int List<T>::getSize() const
{
    return size;
}