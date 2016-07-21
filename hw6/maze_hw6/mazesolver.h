#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "visitedtracker.h"
#include "maze.h"

#include <vector>

/*
 * I didn't want the students to have to deal
 * with function pointers, so I'm making the
 * MazeSolver an object with various solve
 * methods.
 *
 * I won't be offended if anyone wants to refactor
 * this to make specific functions for them to call.
 */

class MazeDisplay;
class Maze;

class MazeSolver
{
public:
    MazeSolver(Maze * m, MazeDisplay * md);

    void solveByBFS();

    void dfs(int r, int c, int& numExplored, std::vector<Direction>& parent, VisitedTracker& vt);

    void solveByDFSIterative();

    void solveByDFSRecursive();

    void solveByAStar(int heuristicChoice);

    void setMaze(Maze* m) { maze = m; }

private:

    int squareNumber(int r, int c) const;

    int heuristic(int choice, std::pair<int, int> curr, std::pair<int, int> goal);

    Maze * maze;
    MazeDisplay * display;
};

#endif // MAZESOLVER_H
