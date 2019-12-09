#pragma once

#include <cassert>

template <typename T>
class List {
public:
    //// Iterators for const and non-const access
	class Iterator;
	class ConstIterator;

	List();
    List(const List<T> &other);
    List<T> &operator=(const List<T> &other);
    ~List();

	/// Remove all elements from the list
	void clear();

	//// Iterator access
    Iterator      begin()       {return Iterator(dummy.next);}
    ConstIterator begin() const {return ConstIterator(dummy.next);}

	Iterator      end()       {return Iterator(&dummy);}
	ConstIterator end() const {return ConstIterator(&dummy);}

	/// Element access for both ends
	void popBack();
	void popFront();
	void pushFront(const T &value);
	void pushBack(const T &value);

	void insertAfter(const Iterator &it, const T &value);
	void insertBefore(const Iterator &it, const T &value);
	void remove(const Iterator &it);

	/// Steal all elements from @other and insert them at @where
	void splice(List<T> &other, const Iterator& where);

	/// Steal all elements from @other and insert them after the last element
	void splice(List<T> &other);

	//// Informative functions
	bool isEmpty() const;
	int getSize() const;

private:
    struct Node;

    Node dummy;
    int size = 0;

    void insertAfterNode(Node *node, const T &value);
    void removeNode(Node *node);
    void copy(const List<T> &other);
};

template <typename T>
struct List<T>::Node {
    Node() = default;
    Node(const T &data) : data(data) {}

    Node *prev;
    Node *next;
    T data;
};

#include "List.inl"
#include "Iterator.inl"
#include "ConstIterator.inl"