#include "a1q2additional.h"

int findPath (Maze& theMaze, const Coord& start, const Coord& end, Coord path[])
{
    return 0;

    std:cout << "end coords = " << end.x << ", " << end.y << std::endl;
    int count = 0;
    findPath (theMaze, start, end, path, count);
    return count;
}