#pragma once

#include <iostream>
#include <limits>

#include "BinaryTreeNode.hpp"
template <typename T>
struct BinaryTreeNode;

template<typename T>
class BinaryTree
{
    friend std::ostream& operator<<(std::ostream& out, const BinaryTree<T>& tree)
    {
        serializeTree(tree.root, out);
        return out;
    }

    friend std::istream& operator>>(std::istream& in, BinaryTree<T>& tree)
    {
        tree.root = deserializeTree(in);
        return in;
    }

public:
    BinaryTree();
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree(BinaryTree<T>&& other);

    BinaryTree<T>& operator=(const BinaryTree<T>& other);
    BinaryTree<T>& operator=(BinaryTree<T>&& other);

    ~BinaryTree();

    bool isBST() const;
    bool isBalanced() const;
    bool isPerfectlyBalanced() const;
    int size() const;

    void makeTreeBST();

    void insert(const T& value);
    void remove(const T& value);

private:

    static bool allLt(const T& val, BinaryTreeNode<T>* r);
    static bool allGt(const T& val, BinaryTreeNode<T>* r);
    static bool isBST(const BinaryTreeNode<T>* r);

    static int getHeightOfTree(const BinaryTreeNode<T>* r);

    static bool isPerfect(BinaryTreeNode<T> *root);
    static bool isPerfect(BinaryTreeNode<T> *root, int height, int level = 0);

    static void makeTreeBST(BinaryTreeNode<T>*& root, const T& lowerBound = std::numeric_limits<T>::min(), const T& upperBound = std::numeric_limits<T>::max());

    static BinaryTreeNode<T>* minElement(BinaryTreeNode<T>* root);

    BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, int key);
    static void deleteRoot(BinaryTreeNode<T>*& root);
    static BinaryTreeNode<T>* deleteNode(BinaryTreeNode<T>* root, const T& key);

    static void serializeTree(const BinaryTreeNode<T>* root, std::ostream& out = std::cout);
    static BinaryTreeNode<T>* deserializeTree(std::istream& in);
    static void match(std::istream& in, char expected);

    static BinaryTreeNode<T>* copy(const BinaryTreeNode<T>* r);
    static void del(BinaryTreeNode<T>* r);

private:
    BinaryTreeNode<T>* root;
};

#include "BinaryTree.inl"