#pragma once

struct Point
{
    int x;
    int y;
};

typedef Point T;

struct Node
{
    Node(const T& d) : data(d), next(nullptr) {}

    T data;
    Node* next;
};