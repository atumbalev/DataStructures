//
// Created by atanas on 19.01.20 г..
//

#include "PermutationGenerator.hpp"

PermutationGenerator::PermutationGenerator()
        : arr(nullptr), outputArr(nullptr), len(0), indexes(nullptr), increase(-1) {}

PermutationGenerator::~PermutationGenerator()
{
    delete [] arr;
    delete [] outputArr;
    delete[] indexes;
}

T *PermutationGenerator::GetFirst()
{
    arr = generateList(len);
    outputArr = new T[len];
    indexes = new int[len];

    for (int i = 0; i < len; ++i) {
        indexes[i] = i;
    }

    increase = 0;

    return output();
}

bool PermutationGenerator::HasNext()
{
    return increase != (len - 1);
}

T *PermutationGenerator::GetNext()
{

    // increase is at the very beginning
    if (increase == 0) {

        // swap Index[0] and Index[1]
        std::swap(indexes[increase], indexes[increase + 1]);

        // Update increase
        increase += 1;
        while (increase < len - 1
               && indexes[increase]
                  > indexes[increase + 1]) {
            ++increase;
        }
    }
    else {

        // Value at indexes[increase + 1] is greater than indexes[0]
        // no need for binary search,
        // just swap indexes[increase + 1] and indexes[0]
        if (indexes[increase + 1] > indexes[0]) {
            std::swap(indexes[increase + 1], indexes[0]);
        }
        else {

            // Binary search to find the greatest value
            // which is less than indexes[increase + 1]
            int start = 0;
            int end = increase;
            int mid = (start + end) / 2;
            int tVal = indexes[increase + 1];
            while (!(indexes[mid] < tVal
                     && indexes[mid - 1] > tVal)) {
                if (indexes[mid] < tVal) {
                    end = mid - 1;
                }
                else {
                    start = mid + 1;
                }
                mid = (start + end) / 2;
            }

            // swap
            std::swap(indexes[increase + 1], indexes[mid]);
        }

        // Invert 0 to increase
        for (int i = 0; i <= increase / 2; ++i) {
            std::swap(indexes[i], indexes[increase - i]);
        }

        // Reset increase
        increase = 0;
    }
    return output();
}

T *PermutationGenerator::output()
{
    for (int i = 0; i < len; ++i)
    {
        outputArr[i] = arr[indexes[i]];
    }
    return outputArr;
}

T *PermutationGenerator::generateList(unsigned size)
{
    unsigned baseValue = 1;
    T *list = new T[size];

    for (int i = 0; i < size; ++i)
    {
        list[i] = baseValue;
        baseValue += 2;
    }

    return list;
}

void PermutationGenerator::setLen(unsigned length)
{
    len = length;
}
