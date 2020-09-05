#include "List.h"

template <typename T>
class List<T>::ConstIterator {
private:
    friend class List;
    const Node *current = nullptr;

    /// Private so only List has access to this ctor
    explicit ConstIterator(const Node *node)
            : current(node)
    {}
public:
    ConstIterator() {}

    /// Read access to the contained data
    const T &operator*() {
        return current->data;
    }

    const T *operator->() {
        return &current->data;
    }

    /// Allow access from const ConstIterator
    const T &operator*() const {
        return current->data;
    }

    const T *operator->() const {
        return &current->data;
    }

    /// Compares for iteration termination
    bool operator==(const ConstIterator &other) const {
        return current == other.current;
    }

    bool operator!=(const ConstIterator &other) const {
        return *this != other;
    }

    /// Allow cross-compare with non const Iterator to allow ConstIterator() != list.end()
    bool operator==(const Iterator &other) const {
        return current == other.current;
    }

    bool operator!=(const Iterator &other) const {
        return *this != other;
    }

    ConstIterator &operator++(int) {
        current = current->next;
        return *this;
    }

    ConstIterator operator++() {
        ConstIterator copy(*this);
        current = current->next;
        return copy;
    }

    ConstIterator &operator--(int) {
        current = current->prev;
        return *this;
    }

    ConstIterator operator--() {
        ConstIterator copy(*this);
        current = current->prev;
        return copy;
    }
};