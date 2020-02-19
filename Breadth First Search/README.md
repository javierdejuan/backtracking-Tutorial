# The Breadth First Search Algorithm
<p align="center">
  <img width="520" height="390"  src="https://github.com/javierdejuan/backtracking-Tutorial/blob/master/Breadth%20First%20Search/img/BFS.gif">
</p>
<p align="center">
BFS Algorithm in process.
</p>

## How BFS works?

BFS finds the optimal path between to given nodes. First, we need to build a matrix with the connections path between origin an destination

1) Select a starting point in your maze
2) Push this point into the BFS queue (the pivot)
3) Explore all its neighbours given the possible movements
4) Push every feasable neighbours into the queue.
5) Mark this cell as visited.
6) Store its father (the current pivot)
7) Pop your pivot cell from the queue
8) Select next pivot from the queue
9) Repeat from 3) until you find your destination
9bis) If destination cannot be reached, then the queue empties. Write handle code for this case.

Once your Connection Matrix is filled, iterate through it starting at the destination cell then store each step in a vector. 
Reverse this vector and you will find the path from origin to destination. 

### The Grid Matrix and Connection Matrix

In this example Grid Matrix is:

```C int grid[N][N];
```
Grid is 0 if there is the cell is reachable and -1 if not. Every time we visited a 0 cell, we overwrite it with 2.

Connection Matrix  must contains for each cell in the Grid Matrix the index of its father (ie, the cell in the Grid Matriz previous to the current according to point6))

So, we need to buid a father matrix like this:

`
```C int father[N][N];
```
Before starting the algorithm, initialize this matriz with -1. 

To store each father, we can use its location in a flatten way, that is, the [row][col] element in grid can be indexed stored that way in the father matrix:


```C int father_index = col + NUMBER_OF_ROWS_IN_GRID x row;
```
Now, to retrieve a grid element given its father_index we can do:


```C int row = father_index / NUMBER_OF_ROWS_IN_GRID;
     int col = father_index % NUMBER_OF_ROWS_IN_GRID;
```

# Pseudo code

```C 
#include "pch.h"
#include <stdlib.h>
#include <vector>
#include <queue>


using namespace std;

#define MOVES_ALLOWED 4
#define MAX_MOVES 8
#define N 9

struct point {
	int x;
	int y;
};


point movement[MAX_MOVES] = { { 0, 1},{1,0 },{0,-1 },{-1,0 },{ 1,1 },{ -1,1 },{ -1,-1 },{ 1,-1 }};


point resolvefather(int index, int father[N][N])
{
	point retval = { 0 };

	retval.y = index % N;
	retval.x = index / N;

	return retval;
}


bool isfeasable(int grid[N][N], point& origin)
{
	if (origin.x >= 0  &&  origin.y >= 0 &&
		origin.x <  N  &&  origin.y < N  &&
		grid[origin.x][origin.y] == 0   &&
		grid[origin.x][origin.y] != -2  )
		
		return true;
	
	return false;
}
bool notinBFSqueue(const point& candidate, deque<point>& bfsqueue)
{
	
	for (deque<point>::iterator t = bfsqueue.begin(); t != bfsqueue.end(); ++t)
	{
		if (t->x == candidate.x && t->y == candidate.y)
			return false;
	}
	return true;

}

void initializefather(int father[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			father[i][j] = -1;
}
void unfoldpath(vector<point>& path, int father[N][N],const point& destination)
{
  if (father[destination.x][destination.y] == -1)
		return;
	
	point newdest = resolvefather(father[destination.x][destination.y], father);
	path.push_back(newdest);
	unfoldpath(path, father, newdest);
}

bool BFS(int grid[N][N],  point& origin, const point& destination, int father[N][N],deque<point>& bfsqueue,vector<point>& path)
{
	getchar();
	static int moves = 0;
	bool bretval = false;
	

	if(origin.x==destination.x&&origin.y==destination.y)
	{
		
		path.push_back(destination);
		unfoldpath(path, father, destination);
		reverse(path.begin(), path.end());
		bretval = true;
		
	}
	else if (!bfsqueue.empty())
	{
		
		for (int i = 0; i < MOVES_ALLOWED; i++)
		{
			point candidate = { 0,0 };

			candidate.x = origin.x + movement[i].x;
			candidate.y = origin.y + movement[i].y;

			grid[origin.x][origin.y] = 2;

			if(isfeasable(grid, candidate) && notinBFSqueue(candidate, bfsqueue))
			{
				bfsqueue.push_back(candidate);
				grid[candidate.x][candidate.y] = 2;
				father[candidate.x][candidate.y] = origin.y + N * origin.x;	
				printf("-->[%d,%d]\n", candidate.x, candidate.y);
				moves++;
			}

		}

		bfsqueue.pop_front();

		if(bfsqueue.size())
		{
			origin = bfsqueue.front();
			BFS(grid, origin, destination, father, bfsqueue, path);
		}
		else
		{
			printf("no solution found.");
		}
	}

	return bretval;
}


int main(void)
{
	


	int grid[N][N] = { {-1, -1, -1, -1, 0, -1, -1, -1, -1},
						{-1, -1, -1, 0, 0, -1, -1, -1, -1},
						{-1, -1, -1, -1, 0, -1,-1, -1, -1},
						{-1, -1, -1, 0, 0, -1, -1, -1, -1},
						{-1, 0, 0, -1, 0, 0, 0, 0, -1},
						{ 0, 0, 0,  0, 0, -1, -1, 0,  0},
						{ 0,-1, -1, -1, 0, -1, -1, -1, 0},
						{0, 0, -1, -1, -1, -1, -1, -1, 0},
						{0, 0, 0, 0, 0, -1, -1, -1, 0} };

	int father[N][N] = { -1 };
	deque <point> bfsqueue;
	vector<point> path;
	
	point orig = point{ 8,0 };
	point dest = point{ 8,8 };

	bfsqueue.push_back(orig);
	initializefather(father);
	BFS(grid, orig, dest, father, bfsqueue,path);
	
	return 0;
}

```


