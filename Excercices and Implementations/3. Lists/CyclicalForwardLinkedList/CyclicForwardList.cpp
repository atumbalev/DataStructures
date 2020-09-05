#include "CyclicForwardList.hpp"

CyclicForwardList::CyclicForwardList() : m_tail(nullptr), m_size(0) {}

CyclicForwardList::CyclicForwardList(const CyclicForwardList& other)
{
    copy(other);
}

CyclicForwardList& CyclicForwardList::operator=(const CyclicForwardList& other)
{
    if (this != &other)
    {
        del();
        copy(other);
    }

    return *this;
}

CyclicForwardList::~CyclicForwardList()
{
    del();
}

void CyclicForwardList::pushFront(const std::string& value)
{
    if (!empty())
    {
        Node* node = new Node(value, m_tail->m_next);
        m_tail->m_next = node;
    }
    else
    {
        Node* node = new Node(value);
        m_tail = node;
        m_tail->m_next = node;
    }

    m_size++;
}

void CyclicForwardList::pushBack(const std::string& value)
{
    if (!empty())
    {

        Node* node = new Node(value, m_tail->m_next);
        m_tail->m_next = node;
        m_tail = node;
    }
    else
    {
        Node* node = new Node(value);
        m_tail = node;
        m_tail->m_next = node;
    }

    m_size++;
}

void CyclicForwardList::popBack()
{

    Node* tmp = m_tail->m_next;
    while (tmp->m_next != m_tail)
    {
        tmp = tmp->m_next;
    }

    tmp->m_next = m_tail->m_next;
    delete m_tail;
    m_tail = tmp;

    m_size--;
}

void CyclicForwardList::popFront()
{
    Node* tmp = m_tail->m_next->m_next;
    delete m_tail->m_next;
    m_tail->m_next = tmp;

    m_size--;
}

void CyclicForwardList::insertAfter(Node* it, const std::string& val)
{
    assert(!empty());
    Node* node = new Node(val, it->m_next);
    it->m_next = node;
    ++m_size;
}

Node* CyclicForwardList::remove(Node* it)
{
    assert(!empty());

    if (m_size == 1)
    {
        delete m_tail;
        --m_size;
        return nullptr;
    }

    // if we dont do this we may lose the reference to the head and lose the list
    if (it->m_next == m_tail)
    {
        m_tail = it;
    }

    Node* toDEl = it->m_next;
    it->m_data = toDEl->m_data;
    it->m_next = toDEl->m_next;
    delete toDEl;
    --m_size;
    return it;
}

void CyclicForwardList::sortedInsert(const std::string& value)
{
    if (empty())
    {
        pushBack(value);
        return;
    }

    Node* current = m_tail->m_next;
    do
    {
        current = current->m_next;
    }
    while (current != m_tail->m_next && strcmp(current->m_next->m_data.c_str(), value.c_str()) > 0);

    insertAfter(current, value);

}

void CyclicForwardList::insertionSort()
{
    // Initialize sorted linked list
    CyclicForwardList sorted;

    // Traverse the given linked list and insert every
    // node to sorted
    Node* current = m_tail->m_next;
    do
    {
        Node *next = current->m_next;

        sorted.sortedInsert(current->m_data);

        current = next;
    }
    while (current != m_tail->m_next);

    std::swap(this->m_tail, sorted.m_tail);
    std::swap(this->m_size, sorted.m_size);
}

void CyclicForwardList::print() const
{
    if (empty()) return;

    Node* it = m_tail;
    do
    {
        std::cout << "->" << it->m_data;
        it = it->m_next;
    } while (it != m_tail);
}

size_t CyclicForwardList::size() const
{
    return m_size;
}

bool CyclicForwardList::empty() const
{
    return m_size == 0;
}

void CyclicForwardList::mergeAdjacent()
{
    if (empty()) return;

    Node* it = m_tail->m_next;
    do
    {
        while (compare(it->m_data, it->m_next->m_data))
        {
            it->m_data += "-" + it->m_next->m_data;
            remove(it->m_next);
        }

        it = it->m_next;

    } while (it != m_tail->m_next);
}

bool CyclicForwardList::compare(const std::string& lhs, const std::string& rhs)
{
    char lhsEnd = lhs[lhs.length() - 1];
    char rhsStart = rhs[0];
    return (toLowerCase(lhsEnd) == toLowerCase(rhsStart));
}

char CyclicForwardList::toLowerCase(char c)
{
    if ( c >= 'A' && c <= 'Z')
    {
        c -= ('A' - 'a');
    }

    return c;
}

void CyclicForwardList::copy(const CyclicForwardList& other)
{
    const Node* it = other.m_tail->m_next;
    do
    {
        pushBack(it->m_data);
        it = it->m_next;
    }
    while (it != other.m_tail->m_next);
}

void CyclicForwardList::del()
{
    while (!empty())
    {
        popFront();
    }
}
