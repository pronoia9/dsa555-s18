#include "maze.h"
#include <iostream>

// INCOMPLETE
void findPath (Maze& theMaze, Coord curr, const Coord& end, Coord path[], int& count)
{
    path[count] = curr;
    theMaze.mark(curr);

    std::cout << "count = " << count << "\t\tpath[" << count << "] = " << curr.x << ", " << curr.y << std::endl;

    if (curr == end) { return; }

    Coord N = Coord(curr.x, curr.y+1);
    Coord E = Coord(curr.x+1, curr.y);
    Coord S = Coord(curr.x, curr.y-1);
    Coord W = Coord(curr.x-1, curr.y);

    if (theMaze.isEmpty(N))
    {
        count++;
        findPath(theMaze, N, end, path, count);
    }
    if (theMaze.isEmpty(E))
    {
        count++;
        findPath(theMaze, E, end, path, count);
    }
    if (theMaze.isEmpty(S))
    {
        count++;
        findPath(theMaze, S, end, path, count);
    }
    if (theMaze.isEmpty(W))
    {
        count++;
        findPath(theMaze, W, end, path, count);
    }
    
    count--;
    theMaze.unMark(curr);
}