#include <fstream>
#include <cstring>
#include <string>

#include "Stack.h"

class StringDecompressor
{
public:
    StringDecompressor(const char *inFilename, const char *outFilename);
    StringDecompressor(const StringDecompressor& other) = delete;
    StringDecompressor&operator=(const StringDecompressor& other) = delete;
    ~StringDecompressor();

    std::ostream& stringDecompress();

    static int exprInBracketsLen(const char* str, int pos);
    static char* parseCStringFromStream(std::istream& in);
private:
    void decompress();
    void free();

    struct Parcel;
    Stack<Parcel> st;

    char* compressedString;
    std::ofstream out;
};

//  Parcel struct will be used to populate the stack that simulates recursion
//  It has 2 implicit conversion constructors from int and from c-string
//  the Parcel struct can be fully replaced semantically by either c-string or int
//  thus such implicit conversion is allowed
struct StringDecompressor::Parcel
{
    Parcel() = default;
    Parcel(char *string) : isString(true), str(string), num(0) {}
    Parcel(int number) : isString(false), str(nullptr), num(number) {}


    bool isString;
    char* str;
    int num;
};
