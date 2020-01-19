#include <iostream>
#include <fstream>
#include <vector>
#include "LCRSTree.hpp"
#include "PermutationGenerator.hpp"

#define PLACEHOLDER '.'

class GracefulTree
{
public:
    GracefulTree(const char* inFile, const char* outFile);
    GracefulTree(const GracefulTree& other) = delete;
    GracefulTree& operator=(const GracefulTree& other) = delete;

    void findGraceful()
    {
        T* permutation = generator.GetFirst();

        while (generator.HasNext())
        {
            fill(tree.getRoot(), permutation);
            if (checkIfGraceful())
            {
                tree.print(out);
                return;
            }
            permutation = generator.GetNext();
        }

        std::cout << "The Tree is not graceful!" << std::endl;
    }
    void fill(Node *tree, T *arr);
    bool checkIfGraceful() const;
private:

    std::ofstream out;
    mutable std::vector<bool> hashSet;
    PermutationGenerator generator;
    LCRSTree tree;

    void fill(Node *tree, T *arr, unsigned index);

    bool checkIfGraceful(const Node *r) const;

};
