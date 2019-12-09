#include "StringDecompressor.h"

StringDecompressor::StringDecompressor(const char *inFilename, const char *outFilename)
{
    std::ifstream in(inFilename);
    out.open(outFilename, std::ios::trunc);

    if (!in || !out)
    {
        std::cerr << "Invalid filenames!" << std::endl;
    }

    compressedString = parseCStringFromStream(in);
    in.close();
}

StringDecompressor::~StringDecompressor()
{
    delete [] compressedString;
    out.close();
}

int StringDecompressor::exprInBracketsLen(const char* str, int pos)
{
    int numberOfBrackets = 1;

    int len = 0;
    while (numberOfBrackets > 0)
    {
        ++len;
        if (str[pos + len] == '\\')
        {
            ++len;
        }

        if (str[pos + len] == '(')
        {
            ++numberOfBrackets;
        }

        if (str[pos + len + 1] == ')')
        {
            --numberOfBrackets;
        }

        if (str[pos + len] == '\0')
        {
            throw std::invalid_argument("mismatched brackets!");
        }

    }
    return len;
}

void StringDecompressor::free()
{
    while (!st.empty())
    {
        delete [] st.pop().str;
    }
}

void StringDecompressor::decompress()
{

    //  Not in try catch block because @string came from the outside and is not my responsibility to manage
    st.push(compressedString);

    bool stringMode = false;
    while (!st.empty())
    {
        if(st.top().isString)
        {
            Parcel& cur = st.pop();
            char *str = cur.str;

            for (int i = 0; str[i] != '\0'; ++i)
            {
                if (str[i] == '"')
                {
                    stringMode = !stringMode;
                    continue;
                }

                if (str[i] == '\\')
                {
                    if(stringMode)
                        out << '\\';

                    out << str[++i];
                    continue;
                }

                if (stringMode)
                {
                    out << str[i];
                    continue;
                }

                //  stringMode = false here
                int num = 0;
                while (str[i] >= '0' && str[i] <= '9')
                {
                    num *= 10;
                    num += str[i] - '0';
                    ++i;
                }

                if (num == 0)
                {
                    out << str[i];
                    continue;
                }

                if (str[i] == '(')
                {
                    int lenOfStrInBrackets = exprInBracketsLen(str, i);

                    char *expr = new char[lenOfStrInBrackets + 1];
                    unsigned tmpPos = 0;
                    while (tmpPos < lenOfStrInBrackets)
                    {
                        expr[tmpPos] = str[i + tmpPos + 1];
                        ++tmpPos;
                    }
                    expr[lenOfStrInBrackets] = '\0';

                    //  If there is nothing left of the string nothing will be done
                    //  Instead of pushing a string with only "\0" inside
                    unsigned len = strlen(str) - i - lenOfStrInBrackets - 1;
                    if(len > 1)
                    {
                        char *rest = new char[len];
                        tmpPos = 0;
                        while (tmpPos < len - 1)
                        {
                            rest[tmpPos] = str[i + lenOfStrInBrackets + 2 + tmpPos];
                            ++tmpPos;
                        }
                        rest[len - 1] = '\0';

                        try
                        {
                            st.push(rest);
                        }
                        catch (std::bad_alloc& e)
                        {
                            free();
                            throw;
                        }
                    }


                    try
                    {
                        st.push(expr);
                        st.push(num);
                    }
                    catch (std::bad_alloc& e)
                    {
                        free();
                        throw;
                    }

                    break;
                } else
                {
                    throw std::invalid_argument("All numbers must be followed by brackets!");
                }
            }
        }
        else
        {
            int times = st.pop().num;

            if (times > 0)
            {
                char *grp = st.top().str;

                try
                {
                    st.push(times - 1);
                    st.push(grp);
                }
                catch (std::bad_alloc& e)
                {
                    free();
                    throw;
                }
            }
            else
            {
                delete[] st.pop().str;
            }
        }
    }
    if (stringMode)
    {
        throw std::invalid_argument("Invalid strings");
    }

}

//  Some streams do not support the seek operation(eg: WebSocket)
//  So use of string as a dynamic buffer store the input
//  Instead of creating a buffer of static size (eg: char[256])
char* StringDecompressor::parseCStringFromStream(std::istream& in)
{
    std::string s;
    in >> s;
    char* str = new char[s.length() +1];
    strcpy(str, s.c_str());
    return str;

}

std::ostream& StringDecompressor::stringDecompress()
{
    try
    {
        decompress();
    }
    catch (std::invalid_argument& e)
    {
        std::cerr << e.what();
        exit(69);
    }
    catch (std::bad_alloc& e) // Stack resize can throw bad_alloc
    {
        std::cerr << "Something went terribly wrong!" << std::endl;
        exit(420);
    }

    return out;
}

