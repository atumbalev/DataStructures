#pragma once

#include <string>

struct Node
{
    Node() : m_data(), m_next(nullptr) {}
    explicit Node(std::string data) : m_data(std::move(data)), m_next(nullptr) {}
    Node(std::string data, Node* pNext) : m_data(std::move(data)), m_next(pNext) {}

    Node* m_next;
    std::string m_data;
};