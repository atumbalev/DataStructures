#include "GracefulTree.hpp"

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        GracefulTree gTree(argv[1], argv[2]);
        gTree.findGraceful();
    }

    std::cout << "Enter Input file name";
    char inFile[256];
    std::cin >> inFile;

    std::cout << "Enter Output file name";
    char outFile[256];
    std::cin >> outFile;

    GracefulTree gTree(inFile, outFile);
    gTree.findGraceful();
}