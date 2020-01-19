#include "GracefulTree.hpp"

GracefulTree::GracefulTree(const char *inFile, const char *outFile)
{
    std::ifstream in(inFile);
    if (!in) throw std::invalid_argument("No such file");

    out.open(outFile);

    tree.read(in);
    in.close();

    unsigned size = tree.size();
    generator.setLen(size);
    hashSet.reserve(size * 2 + 1);
}

void GracefulTree::fill(Node *tree, T *arr)
{
    fill(tree, arr, 0);
}

void GracefulTree::fill(Node *tree, T *arr, unsigned index)
{
    if (!tree) return;
    tree->data = arr[index++];
    fill(tree->sibling, arr, index);
    fill(tree->child, arr, index);
}

bool GracefulTree::checkIfGraceful(const Node *r) const
{
    if (!r) return true;

    int rVal = r->data;
    Node *it = new Node{r->data, r->sibling, r->child};

    while (it)
    {
        if (hashSet[abs(it->data - rVal)])
        {
            return false;
        } else
        {
            hashSet[abs(it->data - rVal)] = false;
        }

        it = it->sibling;
    }

    delete it;
    return checkIfGraceful(r->child);
}

bool GracefulTree::checkIfGraceful() const
{
    return checkIfGraceful(tree.getRoot());
}
