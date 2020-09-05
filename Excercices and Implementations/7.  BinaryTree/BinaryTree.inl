#include "BinaryTree.hpp"

template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
    root = copy(other.root);
}

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T>&& other)
{
    root = other.root;
    other.root = nullptr;
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other)
{
    if (this != &other)
    {
        del(root);
        root = copy(other.root);
    }
    return *this;
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& other)
{
    if (this != &other)
    {
        del(root);
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    del(root);
}

template<typename T>
bool BinaryTree<T>::isBST() const
{
    return isBST(root);
}

template<typename T>
bool BinaryTree<T>::isBalanced() const
{
    return std::abs(getHeightOfTree(root->left) - getHeightOfTree(root->right)) <= 1;
}

template<typename T>
bool BinaryTree<T>::isPerfectlyBalanced() const
{
    return isPerfect(root);
}

template<typename T>
int BinaryTree<T>::size() const
{
    return getHeightOfTree(root);
}

template<typename T>
void BinaryTree<T>::insert(const T& value)
{
    insert(root, value);
}

template<typename T>
void BinaryTree<T>::remove(const T& value)
{
    deleteNode(root, value);
}

template<typename T>
bool BinaryTree<T>::allLt(const T& val, BinaryTreeNode<T>* r)
{
    if (!r) return true;

    return r->data <= val &&
           allLt(val, r->left) &&
           allLt(val, r->right);
}

template<typename T>
bool BinaryTree<T>::allGt(const T& val, BinaryTreeNode<T>* r)
{
    if (!r) return true;

    return r->data >= val &&
           allGt(val, r->left) &&
           allGt(val, r->right);
}

template<typename T>
bool BinaryTree<T>::isBST(const BinaryTreeNode<T>* r)
{
    if (!r) return true;

    return isBST(r->left) &&
           isBST(r->right) &&
           allLt(r->data, r->left) &&
           allGt(r->data, r->right);
}

template<typename T>
int BinaryTree<T>::getHeightOfTree(const BinaryTreeNode<T>* r)
{
    if (!r) return 0;
    return std::max(getHeightOfTree(r->left), getHeightOfTree(r->right)) + 1;
}

template<typename T>
bool BinaryTree<T>::isPerfect(BinaryTreeNode<T>* root, int height, int level)
{
    if (root == nullptr)
        return true;

    if (root->left == nullptr && root->right == nullptr)
        return (height == level + 1);

    if (root->left == NULL || root->right == NULL)
        return false;

    return isPerfect(root->left, height, level + 1) &&
           isPerfect(root->right, height, level + 1);
}

template<typename T>
bool BinaryTree<T>::isPerfect(BinaryTreeNode<T>* root)
{
    int d = getHeightOfTree(root);
    return isPerfect(root, d);
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::insert(BinaryTreeNode<T>* node, int key)
{
    if (node == nullptr) return new BinaryTreeNode<T>(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}

template<typename T>
void BinaryTree<T>::makeTreeBST(BinaryTreeNode<T>*& root, const T& lowerBound, const T& upperBound)
{
    if (!root) return;
    makeTreeBST(root->left, lowerBound, upperBound < root->data ? upperBound : root->data);
    makeTreeBST(root->right, lowerBound > root->data ? lowerBound : root->data, upperBound);
    if (root->data < lowerBound || root->data > upperBound)
    {
        deleteRoot(root);
    }

}

template<typename T>
void BinaryTree<T>::deleteRoot(BinaryTreeNode<T>*& root)
{
    if (!root) return;

    if(!root->left)
    {
        BinaryTreeNode<T>* temp = root->right;
        delete root;
        root = temp;
        return;
    }
    if(!root->right)
    {
        BinaryTreeNode<T>* temp = root->left;
        delete root;
        root = temp;
        return;
    }

    BinaryTreeNode<T> *min = minElement(root->right);
    root->data = min->data;
    root->right = deleteNode(root->right, min->data);
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::minElement(BinaryTreeNode<T>* root)
{
    BinaryTreeNode<T> *temp = root;

    while(temp && temp->left)
    {
        temp=temp->left;
    }

    return temp;
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::deleteNode(BinaryTreeNode<T>* root, const T& key)
{
    if(!root) return nullptr;

    if(key < root->data)
        root->left = deleteNode(root->left, key);

    else if(key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        if(!root->left)
        {
            BinaryTreeNode<T>* temp = root->right;
            delete root;
            return temp;
        }
        if(!root->right)
        {
            BinaryTreeNode<T>* temp = root->left;
            delete root;
            return temp;
        }

        BinaryTreeNode<T> *nx = minElement(root->right);
        root->data=nx->data;
        root->right=deleteNode(root->right,nx->data);
        return root;
    }
    return root;
}

template<typename T>
void BinaryTree<T>::serializeTree(const BinaryTreeNode<T>* root, std::ostream& out)
{
    if (!root)
    {
        out << "()";
        return;
    }

    out << '(' << root->data;
    out << ' ';
    serializeTree(root->left, out);
    out << ' ';
    serializeTree(root->right, out);
    out << ')';
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::deserializeTree(std::istream& in)
{
    match(in, '(');

    if (in.peek() == ')')
    {
        in.ignore();
        return nullptr;
    }

    BinaryTreeNode<T>* root = new BinaryTreeNode<T>();
    in >> root->data;

    match(in, ' ');

    root->left = deserializeTree(in);

    match(in, ' ');

    root->right = deserializeTree(in);

    match(in, ')');
    return root;
}

template<typename T>
void BinaryTree<T>::match(std::istream& in, char expected)
{
    char real;
    real = in.get();
    if (real != expected)
    {
        throw std::runtime_error("Malformed Tree");
    }
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::copy(const BinaryTreeNode<T>* r)
{
    if (!r) return nullptr;

    BinaryTreeNode<T>* copy = new BinaryTreeNode<T>(r->data);
    copy->left = copy(r->left);
    copy->right = copy(r->right);
    return copy;
}

template<typename T>
void BinaryTree<T>::del(BinaryTreeNode<T>* r)
{
    if (!r) return;

    del(r->left);
    del(r->right);
    delete r;
}

template<typename T>
void BinaryTree<T>::makeTreeBST()
{
    makeTreeBST(root);
}
