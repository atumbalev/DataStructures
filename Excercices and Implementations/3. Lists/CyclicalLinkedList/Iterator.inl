#include "List.h"

template <typename T>
class List<T>::Iterator {
private:
    friend class List;
    Node *current = nullptr;

    /// Private so only List has access to this ctor
    explicit Iterator(Node *node)
            : current(node)
    {}
public:
    Iterator() {}

    T &operator*() {
        return current->data;
    }

    T *operator->() {
        return &current->data;
    }

    /// Allow for const Iterator to have access to the data
    const T &operator*() const {
        return current->data;
    }

    const T *operator->() const {
        return &current->data;
    }

    bool operator==(const Iterator &other) const {
        return current == other.current;
    }

    bool operator!=(const Iterator &other) const {
        return !(*this == other);
    }

    Iterator &operator++(int) {
        current = current->next;
        return *this;
    }

    Iterator operator++() {
        Iterator copy(*this);
        current = current->next;
        return copy;
    }

    Iterator &operator--(int) {
        current = current->prev;
        return *this;
    }

    Iterator operator--() {
        Iterator copy(*this);
        current = current->prev;
        return copy;
    }
};