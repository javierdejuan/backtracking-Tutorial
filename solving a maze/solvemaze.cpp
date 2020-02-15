// solvemaze.cpp 
/*
	A NxN matrix represents a maze. Cells with number 0 are passing cells. Cells with number 1 are no passing cells.
	You have to find a path from cell [0,0] to cell [N-1,N-1] avoind non passing cells.

*/

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <vector>


using namespace std;


// N is used for the size of Maze grid. 
// Size will be NxN 
#define N 9 

// In this array we will store visited cells to avoid recalculating subsolutions
int lookup[N][N] = { 0 };

// Point structure to store the path
struct point {
	int x;
	int y;
};


// print function
void printHeader(void)
{
	cout << "*-------------------------------------------------------------------------------------------------\n";
	cout << "*			Understanding backracking.\n";
	cout << "*			Example #1 Solving a Maze\n";
	cout << "*			Entering the maze at cell [0,0]\n";
	cout << "*			you have to reach cell [8,8]\n";
	cout << "*			Cells with -1 are non-passing points" << endl;
	cout << "*			©Javier de Juan February 2020\n";
	cout << "*--------------------------------------------------------------------------------------------------\n";
}

// prints partial path for learning purposes
void printPath(vector<point>& path)
{
	cout << "path so far:" << endl;

	for (vector<point>::iterator t = path.begin(); t != path.end(); ++t)
	{
		std::cout << "[" << t->x << "," << t->y << "]";
	}
	cout << "\npartial solution cost:" << path.size() << endl;

}

// prints grid for learning purposes
void printGrid(int grid[N][N], vector<point>& path, int rowg, int colg, const int depth = 0, const int moves = 0)
{
	system("CLS");
	printHeader();
	printPath(path);

	cout << endl;
	cout << "row:" << rowg << " col:" << colg << endl;

	cout << "solvepath call number:" << depth << " moves:" << moves << endl;

	for (int col = 0; col < N; col++) {
		cout << "---------";

	}
	cout << endl;
	cout << endl;
	for (int row = 0; row < N; row++)
	{
		cout << "row# " << row << " - ";

		for (int col = 0; col < N; col++) {

			if (lookup[row][col] == -1)
				cout << "-" << "\t";
			else if (col == colg && row == rowg)
				cout << "*" << grid[row][col] << "\t";
			else
				cout << grid[row][col] << "\t";

		}
		cout << endl;
	}
	for (int col = 0; col < N; col++) {
		cout << "---------";

	}
	cout << endl;
	cout << "\t";
	for (int col = 0; col < N; col++) {
		cout << "col#" << col << "\t";

	}
	cout << "\n\nPress <ENTER> to continue" << endl;
	getchar();

}


// array containing movements allowed for each cell candidate
const int movem[8][2] = { {1,1} ,{1,0} ,{1,-1},{0,-1}, {-1,-1},{-1,0},{-1,1} ,{0,1} };

// solve function
bool solvemaze(vector <point>& path, int grid[N][N], int row, int col)
{
	static int moves = 0; // counts the number of decisions taken
	static int depth = 0; // everytime we enter solvemaze this variable is increased

	// Since we have to reach the bottom right corner, this is our exit condition:

	if (grid[N - 1][N - 1] == 3) // exit condition, path completed
	{

		cout << "found solution in " << moves << " moves" << endl;
		cout << "depth:" << depth << endl;
		printPath(path);
		cout << "unfolding solvemaze function calls:" << endl;

		return true;
	}
	else // path is incomplete, let's complete it
	{

		int row_c = 0;	// here we are going to store our new candidate
		int col_c = 0;

		int revrow = 0;	// here we are going to store previous candidate
		int revcol = 0;

		depth++;				// we update the stack count of recursive calls

		for (int i = 0; i < 8; i++)			   // for each movement allowed in our movem array
		{

			row_c = movem[i][0] + row;		   // instanciating candidate
			col_c = movem[i][1] + col;

			if ((row_c >= 0 && col_c >= 0) &&	// if candidate is in the grid
				(row_c < N  && col_c < N) &&	// if candidate is in the grid
				grid[row_c][col_c] == 0 &&	// if candidate is a non blocking point
				lookup[row_c][col_c] != -1)	// if candidate has not been tested
			{

				grid[row_c][col_c] = 3;			// write grid cell with value 3
				revrow = row;				// Keep previous candidate 
				revcol = col;				// (if backtracking is needed)
				row = row_c;				// move to next candidate
				col = col_c;

				point candidate;			// store point for printing path

				candidate.x = row;
				candidate.y = col;

				path.push_back(candidate);		// update path for printing purposes

				moves++;				// update moves
				printGrid(grid, path, row, col, depth, moves);

				// now move to the next candidate, recursive call

				if (solvemaze(path, grid, row, col))
				{
					// if true, we are done, maze is complete
					cout << "Solution Found! emerging to surface:" << depth-- << endl;
					return true;
				}
				else // if solvemaze failed, that means we have reached a non valid exit cell
				{

					// backtracking code block

					cout << "path failed! Restoring last decision" << endl;
					cout << "bactracking row:" << row << " col:" << col << " depth:" << depth << " moves:" << moves << endl;

					getchar();

					// we need to resotre previous values

					grid[row_c][col_c] = 0;		// initial grid value
					lookup[row_c][col_c] = -1;	// store invalid candidate to avoid repeating same searchs
					col = revcol;			// revert to previous candidate column
					row = revrow;			// revert to previoous candidate row
					moves++;			// update number of decisions
					depth--;			// since backtracking is triggered, we move up in the stack of recursive calls
					path.pop_back();		// update path 
					printGrid(grid, path, row, col, depth, moves);

					// end backtracking coding block

				}
			}

		}
	}
	// we reached a blocking point
	// here bactracking is triggered
	return false;
}
// driver function
int main()
{

	int grid[N][N] = { {0, 0, 1, 1, 0, 1, 1, 0, 0},
			{1, 1, 0, 0, 0, 1, 0, 0, 0},
			{0, 0, 1, 1, 0, 1, 0, 0, 1},
			{0, 0, 0, 0, 0, 1, 0, 1, 0},
			{1, 1, 0, 1, 0, 1, 0, 0, 1},
			{0, 0, 0, 1, 0, 0, 1, 1, 0},
			{0, 1, 1, 1, 1, 1, 0, 1, 0},
			{1, 1, 0, 1, 0, 1, 1, 1, 0},
			{1, 0, 0, 0, 0, 1, 0, 1, 0} };
	vector <point> path;
	printGrid(grid, path, 0, 0);
	solvemaze(path, grid, -1, -1);
	return 0;
}

