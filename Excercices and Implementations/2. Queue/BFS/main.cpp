#include <iostream>
#include <fstream>
#include <stack>

const char* newMap = "5\n"
                     "...#.\n"
                     ".##.#\n"
                     ".#..#\n"
                     ".#.##\n"
                     ".....";

char** mapBuilder(std::istream& in)
{
    std::string s;
    int size = 6;

    char** map = new char*[size];
    for (int i = 0; i < size; ++i)
    {
        map[i] = new char[size];
        in.ignore();
        in.getline(map[i], size);
    }

    return map;
}

char** constructMap()
{
    std::ofstream createMap("map.txt", std::ios::trunc);
    createMap << newMap;
    createMap.flush();
    createMap.close();

    std::ifstream map("map.txt");
    return mapBuilder(map);
}

void sink(char** map, int i, int j)
{
    map[i][j] = '.';
}

int numberOfIslands()
{
    char** map = constructMap();
    int count = 0;

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            if (map[i][j] == '#')
            {
                sink(map, i, j);
                ++count;


            }
        }
    }
}