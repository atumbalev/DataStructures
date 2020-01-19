//
// Created by atanas on 19.01.20 г..
//

#include "LCRSTree.hpp"

void LCRSTree::print(std::ostream &out) const
{
    print(root, out);
}

void LCRSTree::read(std::istream &in)
{
    del(root);
    root = m_read(in);
}

Node*& LCRSTree::getRoot()
{
    return root;
}

void LCRSTree::del(Node *r)
{
    if (!r) return;

    del(r->sibling);
    del(r->child);
    delete r;
}

unsigned LCRSTree::getSizeOfTree(Node *r) const
{
    if (!r) return 0;
    return 1 + getSizeOfTree(r->sibling) + getSizeOfTree(r->child);
}

void LCRSTree::print(Node const *root, std::ostream &out) const
{
    if (!root)
    {
        out << "()";
        return;
    }

    out << "(" << root->data;
    print(root->sibling, out);
    print(root->child, out);
    out << ")";
}

Node *LCRSTree::m_read(std::istream &in)
{
    in.ignore(); // (

    if (in.peek() == ')')
    {
        in.ignore(); // )
        return nullptr;
    }

    int data = 0;
    if (in.peek() == PLACEHOLDER) in.ignore();
    else in >> data;

    Node* left = m_read(in);
    Node* right = m_read(in);
    in.ignore();  // )
    return new Node{data, left, right};
}

unsigned LCRSTree::size() const
{
    return getSizeOfTree(root);
}

const Node* LCRSTree::getRoot() const
{
    return root;
}
