#include <fstream>
#include "BinaryTree.hpp"

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::ifstream file(argv[1]);
        if (!file.is_open())
        {
            std::cerr << "Invalid file name!" << std::endl;
            return -1;
        }

        BinaryTree<int> tree;

        try
        {
            file >> tree;
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            return -2;
        }

        if (!tree.isPerfectlyBalanced())
        {
            if (!tree.isBalanced())
            {
                std::cout << "Tree is not balanced!" << std::endl;
            }
            else
            {
                std::cout << "Tree is balanced, but not perfectly balanced" << std::endl;
            }
        }
        else
        {
            std::cout << "Tree is perfectly balanced, as all things should be" << std::endl;
        }

        if (!tree.isBST())
        {
            std::cout << "Tree is not BST, a function to remove all elements, that ruin the order is getting called!" << std::endl;
            std::cout << "Before: " << tree << std::endl;
            tree.makeTreeBST();
            std::cout << "After: " << tree << std::endl;
            return 0;
        }

        std::cout << "Tree: " << tree << std::endl;
        return 0;
    }
}
