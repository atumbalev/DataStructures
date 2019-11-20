#pragma once

#include <stdexcept>
#include <fstream>
#include "Array Stack/Stack.h"

bool bigger(char newBracket, char oldBracket)
{
    //ASCII char for a closing bracket is always after the ASCII char for the corresponding opening bracket
    return newBracket > oldBracket;
}

bool closes(char newBracket, char oldBracket)
{
//    ASCII chars for () are next to each other
    if (newBracket == ')')
    {
        return oldBracket == '(';
    }

//    ASCII chars for [] {} are 2 chars apart
    return oldBracket == newBracket - 2;
}

bool expressionValidator(const char* filename)
{
    std::ifstream file(filename);

    std::string expr;
    file >> expr;

    Stack st;

    for (int i = 0; i < expr.length(); ++i)
    {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
        {
            if (!st.empty() && bigger(expr[i], st.top()))
            {
                return false;
            }

            st.push(expr[i]);
        } else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}')
        {
            if (st.empty() || !closes(expr[i], st.top()))
            {
                return false;
            }

            try
            {
                st.pop();
            }
            catch (std::out_of_range& e)
            {
                return false;
            }
        }
        file.close();
        return st.empty();

    }
}
