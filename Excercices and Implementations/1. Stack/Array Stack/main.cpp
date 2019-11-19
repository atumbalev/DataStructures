#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"

bool expressionValidator(const char* filename)
{
    std::ifstream file(filename);

    std::string expr;
    file >> expr;

    Stack st;

    for (int i = 0; i < expr.length(); ++i)
    {
        if(expr[i] == '(' )
        {
            st.Push(expr[i]);
        }
        if(expr[i] == ')')
        {
            try
            {
                st.Pop();
            }
            catch (std::out_of_range& e)
            {
                return false;
            }
        }
    }
    file.close();
    return st.Empty();

}

int main()
{
    const char* filename = "test";
    std::ofstream f(filename, std::ios::trunc);

    f << "((()))()";

    f.close();

    std::cout << std::boolalpha << expressionValidator(filename);
}