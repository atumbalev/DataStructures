#pragma once

typedef int T;

struct Node
{
    Node(const T& d) : data(d), next(nullptr) {}

    T data;
    Node* next;
};