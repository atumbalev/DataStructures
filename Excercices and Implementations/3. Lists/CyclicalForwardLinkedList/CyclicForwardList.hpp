#include <cassert>
#include <iostream>
#include <cstring>
#include "Node.hpp"

class CyclicForwardList
{
public:
    CyclicForwardList();
    CyclicForwardList(const CyclicForwardList& other);
    CyclicForwardList& operator=(const CyclicForwardList& other);
    ~CyclicForwardList();

    void pushFront(const std::string& value);
    void pushBack(const std::string&value);

    void popBack();
    void popFront();

    void insertAfter(Node* it, const std::string& val);
    Node* remove(Node* it);

    void sortedInsert(const std::string& value);
    void insertionSort();

    void print() const;
    size_t size() const;
    bool empty() const;

    void mergeAdjacent();
private:
    Node* m_tail{};
    size_t m_size{};

    static bool compare(const std::string& lhs, const std::string& rhs);

    static char toLowerCase(char c);

    void copy(const CyclicForwardList& other);
    void del();
};