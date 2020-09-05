#include <iostream>
#include "List.h"

int main()
{
    List<int> l;
    l.pushBack(1);
    l.pushBack(2);
    l.pushFront(3);

    for (auto a : l)
    {
        std::cout << a;
    }

    return 0;
}
