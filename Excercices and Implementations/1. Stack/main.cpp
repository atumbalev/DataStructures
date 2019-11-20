#include <iostream>

#include "ExpressionValidator.h"

int main()
{
//    expressionValidator works with files and streams
    char expr[50];
    std::cin >> expr;
    std::cout << std::boolalpha << expressionValidator(expr) << std::endl;
}
