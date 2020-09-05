#include <iostream>
#include "CyclicForwardList.hpp"

int main()
{
    std::cout << "Please input words" << std::endl << "To stop the input type --" << std::endl;

    CyclicForwardList list;
    std::string words;
    while (true)
    {
        std::cin >> words;
        if (words == "--")
        {
            break;
        }
        list.pushBack(words);
    }

    list.mergeAdjacent();
    list.insertionSort();
    list.print();
}