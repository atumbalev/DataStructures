#ifndef INC_3_GRACEFULTREENEW_LCRSTREE_HPP
#define INC_3_GRACEFULTREENEW_LCRSTREE_HPP


#include <fstream>
#include <iostream>

#define PLACEHOLDER '.'
typedef int T;

struct Node
{
    T data;
    Node* sibling;
    Node* child;
};

class LCRSTree
{
public:
    LCRSTree() : root(nullptr) {}
    LCRSTree(const LCRSTree& other) = delete;
    LCRSTree& operator=(const LCRSTree& other) = delete;
    ~LCRSTree() {del(root);}

    void print(std::ostream& out = std::cout) const;
    void read(std::istream& in);
    unsigned size() const;
    Node*& getRoot();
    const Node* getRoot() const;

private:

    Node* root;

    void del(Node* r);

    unsigned getSizeOfTree(Node* r) const;
    void print(Node const* root, std::ostream& out) const;
    Node* m_read(std::istream& in);
};


#endif //INC_3_GRACEFULTREENEW_LCRSTREE_HPP
