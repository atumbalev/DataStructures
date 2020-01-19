#include "LCRSTree.hpp"

class PermutationGenerator {
private:
    T* arr;
    T* outputArr;
    int len;
    int* indexes;

    // The index of the first "increase"
    // in the Index array which is the smallest
    // i such that indexes[i] < indexes[i + 1]
    int increase;

public:
    PermutationGenerator();
    PermutationGenerator(const PermutationGenerator& other) = delete;
    PermutationGenerator& operator=(const PermutationGenerator& other) = delete;
    ~PermutationGenerator();

    // Initialize and output
    // the first permutation
    T* GetFirst();

    // Function that returns true if it is
    // possible to generate the next permutation
    bool HasNext();

    // output the next permutation
    T* GetNext();
    void setLen(unsigned length);

private:
    // Function to output the input array
    T* output();

    T *generateList(unsigned size);

};