#include "StringDecompressor.h"

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        StringDecompressor decompressor(argv[1], argv[2]);
        decompressor.stringDecompress();
        return 0;
    }

    std::cout << "Enter Input filename: " << std::endl;
    std::string inFile;
    std::cin >> inFile;

    std::cout << "Enter Output filename: " << std::endl;
    std::string outFile;
    std::cin >> outFile;

    StringDecompressor stringDecompressor(inFile.c_str(), outFile.c_str());
    stringDecompressor.stringDecompress();
    return 0;
}