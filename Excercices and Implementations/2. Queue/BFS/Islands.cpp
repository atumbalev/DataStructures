#include <fstream>
#include <queue>
#include <iostream>

struct Point
{
    int x, y;
};

char **generateArray(unsigned size)
{
    char **arr = new char *[size];

    for (int i = 0; i < size; ++i)
    {
        arr[i] = new char[size];
    }

    return arr;
}

void fill(char **arr, unsigned size, std::ifstream &in)
{
    for (unsigned i = 0; i < size; ++i)
    {
        for (unsigned j = 0; j < size; ++j)
        {
            in >> arr[i][j];
        }
    }
}

void sink(char **arr, Point p)
{
    arr[p.x][p.y] = '.';
}

void checkForLand(char **arr, Point p, unsigned size, std::queue<Point> &q)
{
    for (int xOffset = -1; xOffset <= 1; ++xOffset)
    {
        for (int yOffset = -1; yOffset <= 1; ++yOffset)
        {
            if (abs(xOffset) == abs(yOffset))
                continue;

            Point cur{p.x + xOffset, p.y + yOffset};

            if (cur.x >= size || cur.x < 0)
            { continue; }
            if (cur.y >= size || cur.y < 0)
            { continue; }

            if (arr[cur.x][cur.y] == '#')
            {
                sink(arr, cur);
                q.push(cur);
            }
        }
    }
}

int numberOfIslands(unsigned n, std::ifstream &in)
{
    char **map = generateArray(n);
    fill(map, n, in);
    std::queue<Point> q;
    int count = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (map[i][j] == '#')
            {
                ++count;
                q.push({i, j});
                while (!q.empty())
                {
                    Point pos = q.front();
                    sink(map, pos);
                    q.pop();
                    checkForLand(map, pos, n, q);
                }
            }
        }
    }
    return count;
}

void drawMap()
{
    std::ofstream map("map.txt", std::ios::trunc);

    map << "...#."
           ".##.#"
           ".#..#"
           ".#.##"
           ".....";

    map.flush();
    map.close();
}

int main()
{
    drawMap();
    std::ifstream map("map.txt");

    std::cout << numberOfIslands(5, map);

    return 0;
}
