#include "mazesolver.h"
#include "mazedisplay.h"
#include "heap.h"

#include <QMessageBox>
#include <queue>
#include <stack>
#include <stdlib.h>

#include <cmath>
#include <climits>
#include <iostream> 

MazeSolver::MazeSolver(Maze * m, MazeDisplay * md)
    : maze(m), display(md)
{}

void MazeSolver::solveByDFSRecursive() // need to use this as a helper function 
{
    // TODO:  This is for you to implement!
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent(numSquares);
    int numExplored = 0;

    r = maze->getStartRow();
    c = maze->getStartCol();

    vt.setVisited(r, c);

    dfs(r, c, numExplored, parent, vt); // calling the dfs recursive function

}

void MazeSolver::dfs(int r, int c, int& numExplored, std::vector<Direction>& parent, VisitedTracker& vt)
{
    bool b_RIGHT = FALSE;
    bool b_LEFT = FALSE;
    bool b_DOWN = FALSE;
    bool b_UP = FALSE;

    if(r == maze->getGoalRow() && c == maze->getGoalCol()) // base case to print out the DFS
    {
        std::vector<Direction> path;
        std::stack<Direction> st;
        
        while( r != maze->getStartRow() || c != maze->getStartCol())
        {
            st.push( parent[ squareNumber(r,c) ]);
            
            switch(st.top())
            {
            case UP: r++; break;
            case DOWN: r--; break;
            case LEFT: c++; break;
            case RIGHT: c--; break;
            }
        }
        
        int length = 0;

            while ( ! st.empty() )
            {
                length++;
                path.push_back(st.top());
                st.pop();
            }
                
        cerr << length << endl;
        
        display->reportSolution(path, vt, numExplored);
        
        return;
    }
    else{

        // need to reverse the order because no longer taking off the top of the stack

        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            vt.setVisited(r, c+1);
            parent[squareNumber(r, c+1)] = RIGHT;
            b_RIGHT = TRUE;
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            vt.setVisited(r, c-1);
            parent[squareNumber(r, c-1)] = LEFT;
            b_LEFT = TRUE;
            
        }
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {   
            vt.setVisited(r+1, c);
            parent[squareNumber(r+1, c)] = DOWN;
            b_DOWN = TRUE;
            
        }
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            vt.setVisited(r-1, c);
            parent[squareNumber(r-1, c)] = UP;
            b_UP = TRUE;
            
        }
    }

    if(b_RIGHT){
        numExplored++;
        dfs(r, c+1, numExplored, parent, vt);
    }

    if(b_LEFT){
        numExplored++;
        dfs(r, c-1, numExplored, parent, vt);
    }

    if(b_DOWN){
        numExplored++;
        dfs(r+1, c, numExplored, parent, vt);
    }
    
    if(b_UP){
        numExplored++;
        dfs(r-1, c, numExplored, parent, vt);
    }  

}

void MazeSolver::solveByAStar(int choice)
{
    // TODO:
    //    if choice is 1, solve by A* using heuristic of "return 0"
    //    else if choice is 2, solve by A* using heuristic of Manhattan Distance
    //    else if choice is 3, solve by A* using heuristic of Euclidean Distance
    // else completely up to you.

    // open is the heap
    // closed is the visited set

    int r, c;

    int cost;

    int numSquares = maze->numRows() * maze->numCols();

    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent(numSquares); // what was my immediate prior direction to get here?
    int numExplored = 0;

    MinHeap< std::pair<int, int> > open(2);

    int** cost_so_far = new int *[maze->numRows()];  // need to keep track of the costs with a 2D array similar to size of Maze
   
    for(int i = 0; i < maze->numRows(); i++){

        cost_so_far[i] = new int[maze->numCols()];

        for(int j = 0; j < maze->numCols(); j++){

        cost_so_far[i][j] = INT_MAX;

        }
    }

    std::pair<int, int> goal = make_pair(maze->getGoalRow(), maze->getGoalCol());

    std::pair<int, int> start = make_pair(maze->getStartRow(), maze->getStartCol());

    open.add(start, 0); // adding start to the minheap

    cost_so_far[start.first][start.second] = 0; // setting start g(n) to 0 

    while(!open.isEmpty()){ // checking if the minheap is empty 

        std::pair<int, int> curr = open.peek();

        r = curr.first;
        c = curr.second;

        // if the end goal is met

        if(vt.isVisited(r, c)){ // if the node has been visited before, then just remove it from the heap

            open.remove();

        }
        else{ // otherwise explore the node

            // break if reach the end node and print

            if(r == maze->getGoalRow() && c == maze->getGoalCol())
            {
                std::vector<Direction> path;
                std::stack<Direction> st;

                while( r != maze->getStartRow() || c != maze->getStartCol())
                {
                    st.push( parent[ squareNumber(r,c) ]);
                    switch( st.top() )
                    {
                        case UP: r++; break; // yes, r++.  I went up to get here...
                        case DOWN: r--; break;
                        case LEFT: c++; break;
                        case RIGHT: c--; break;
                    }
                }
                
                int length = 0;

                while ( ! st.empty() )
                {
                    length++;
                    path.push_back(st.top());
                    st.pop();

                }
                
                cerr << length << endl;

                display->reportSolution(path, vt, numExplored);
                return;
            }

            open.remove(); // remove from the minheap

            cost = cost_so_far[r][c] + 1; // update the cost of curr visiting the neighbor

            if (maze->canTravel(UP, r, c)) // checking each individual node
            {   

                if(cost < cost_so_far[r-1][c]) // if the cost is lower, then add to the minheap 
                { 
                    pair<int, int> p = make_pair(r-1, c); 

                    int new_cost = cost + heuristic(choice, p, goal);
                
                    parent[squareNumber(r-1, c)] = UP; // update the parent 

                    // add to the heap even if you have already explored
                    // update minheap
                    open.add(p, new_cost); 

                    // update the g(n)
                    cost_so_far[r-1][c] = cost;
                }
            }        
            if (maze->canTravel(DOWN, r, c))
            {  

                if(cost < cost_so_far[r+1][c])
                { 
                    pair<int, int> p = make_pair(r+1, c);

                    int new_cost = cost + heuristic(choice, p, goal);
                    
                    parent[squareNumber(r+1, c)] = DOWN;

                    // add to the heap even if you have already explored
                    
                    // update minheap
                    open.add(p, new_cost);

                    // update the g(n)
                    cost_so_far[r+1][c] = cost;
                }
            }
            if (maze->canTravel(LEFT, r, c))
            {

                if(cost < cost_so_far[r][c-1])
                { 
                    pair<int, int> p = make_pair(r, c-1);

                    int new_cost = cost + heuristic(choice, p, goal);
                    
                    parent[squareNumber(r, c-1)] = LEFT;

                    // add to the heap even if you have already explored
                    
                    // update minheap
                    open.add(p, new_cost);

                    // update the g(n)
                    cost_so_far[r][c-1] = cost;
                }
            }
            if (maze->canTravel(RIGHT, r, c))
            {

                if(cost < cost_so_far[r][c+1])
                { 
                    pair<int, int> p = make_pair(r, c+1);

                    int new_cost = cost + heuristic(choice, p, goal);
                    
                    parent[squareNumber(r, c+1)] = RIGHT;

                    // add to the heap even if you have already explored
                    
                    // update minheap
                    open.add(p, new_cost);

                    // update the g(n)
                    cost_so_far[r][c+1] = cost;
                }
            }

            numExplored++; // update the numExplored
            vt.setVisited(r, c); // add curr to the visited set
        }

    }

    for(int i = 0; i < maze->numRows(); i++){ // so no memory leaks
        delete [] cost_so_far[i];
    }
   
    delete [] cost_so_far;

}

int MazeSolver::heuristic(int choice, std::pair<int, int> curr, std::pair<int, int> goal) {

    int sum = 0;

    if(choice == 1){ // 0 
        sum = 0;
    }
    else if (choice == 2){ // Manhattan

        int dx = abs(curr.first - goal.first);
        int dy = abs(curr.second - goal.second);

        sum = (dx + dy);
    }
    else if (choice == 3){ // Euclidean

        int dx = abs(curr.first - goal.first);
        int dy = abs(curr.second - goal.second);

        sum = sqrt((dx * dx) + (dy * dy));
    }

    return sum; 
}

void MazeSolver::solveByDFSIterative()
{
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent(numSquares); // what was my immediate prior direction to get here?
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::stack<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    while(!q.empty())
    {
        std::pair<int, int> v = q.top();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        /* This one if statement is different from the pseudo-code provided
           in lecture, because we want to stop when we've reached the goal.
           The code provided in lecture was for if you wanted to do a BFS
           that explored the entire graph.
        */
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;

            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);
                switch( st.top() )
                {
                case UP: r++; break; // yes, r++.  I went up to get here...
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }
            int length = 0;

            while ( ! st.empty() )
            {
                length++;
                path.push_back(st.top());
                st.pop();
            }
                
            cerr << length << endl;

            display->reportSolution(path, vt, numExplored);
            return;
        }

        /*
         * Now we're back to code that looks like the pseudo-code you've seen.
         * The difference here is that we aren't keeping track of distances;
           that's similar to the difference above.  You could add, and ignore,
           the vector that would result if you wanted to do so.
         */

        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }
        // Note:  this is NOT "else if" ...
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}

void MazeSolver::solveByBFS()
{
    /* In lecture on Tuesday March 22, we had a graph
       with vertices numbered 0 to n-1, inclusive.
       Instead, we have vertices with two numbers,
       row and col, in the range:
       [0, maze->numRows()-1], [0, maze->numCols() -1 ]
       to assign each a unique number [0, maze->numRows() * maze->numCols() -1]
       we will say that maze square (r,c) is really number
       r * maze->numCols() + c
    */
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::queue<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    while( ! q.empty() )
    {
        std::pair<int, int> v = q.front();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        /* This one if statement is different from the pseudo-code provided
           in lecture, because we want to stop when we've reached the goal.
           The code provided in lecture was for if you wanted to do a BFS
           that explored the entire graph.
        */
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;

            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);
                switch( st.top() )
                {
                case UP: r++; break; // yes, r++.  I went up to get here...
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }

            int length = 0;

            while ( ! st.empty() )
            {
                length++;
                path.push_back(st.top());
                st.pop();
            }
                
            cerr << length << endl;

            display->reportSolution(path, vt, numExplored);
            return;
        }

        /*
         * Now we're back to code that looks like the pseudo-code you've seen.
         * The difference here is that we aren't keeping track of distances;
           that's similar to the difference above.  You could add, and ignore,
           the vector that would result if you wanted to do so.
         */
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }
        // Note:  this is NOT "else if" ...
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}


int MazeSolver::squareNumber(int r, int c) const
{
    return maze->numCols() * r + c;
}