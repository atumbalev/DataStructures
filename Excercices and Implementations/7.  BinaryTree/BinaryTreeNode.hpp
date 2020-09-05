#pragma once

template <typename T>
struct BinaryTreeNode
{
    BinaryTreeNode() = default;
    BinaryTreeNode(const T& data) : data(data), left(nullptr), right(nullptr) {}
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};