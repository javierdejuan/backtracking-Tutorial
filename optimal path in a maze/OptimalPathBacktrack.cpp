#include "pch.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <vector>

#include <algorithm>

#include <windows.h>
#include "doublebuffertools.h"

using namespace std;

const int movem4[4][2] = { {1,0} ,{0,1},{-1,0},{0,-1} };

#define N 9
int lookup[N][N] = { 0 };

struct point {
	int x;
	int y;
};

int  printHeaderEx(int& line)
{

	WCHAR aux[WIDTH] = { 0 };
	int len = 0;

	len=swprintf(aux, (size_t)WIDTH, L"*-------------------------------------------------------------------------------------------------");
	writeLine(aux, line++, len);
	len=swprintf(aux, (size_t)WIDTH, L"*                         Understanding backracking.");
	writeLine(aux, line++, len);
	len=swprintf(aux, (size_t)WIDTH, L"*                         Example #2 Finding best solution in a Maze");
	writeLine(aux, line++, len);
	len=swprintf(aux, (size_t)WIDTH, L"*                         Entering the maze at a given point");
	writeLine(aux, line++, len);
	len=swprintf(aux, (size_t)WIDTH, L"*                         you have to reach a destination cell");
	writeLine(aux, line++, len);
	len=swprintf(aux, (size_t)WIDTH, L"*                         through the optimal path");
	writeLine(aux, line++, len);
	len=swprintf(aux, (size_t)WIDTH, L"*                         ©Javier de Juan February 2020");
	writeLine(aux, line++, len);
	len=swprintf(aux, (size_t)WIDTH, L"*--------------------------------------------------------------------------------------------------");
	writeLine(aux, line++, len);

	return line;

}

void  printPath(vector<point>& path, int& line)
{
	int len = 0;
	WCHAR aux[WIDTH] = { 0 };
	WCHAR aux2[WIDTH] = { 0 };

	
	len = swprintf(aux, (size_t)WIDTH, L"Path so far:");
	writeLine(aux, line++, len);
    memset(aux,0, (size_t)WIDTH);

	for (vector<point>::iterator t = path.begin(); t != path.end(); ++t)
	{
		swprintf(aux2, (size_t)WIDTH, L"[%d,%d]",t->x , t->y);
		wcscat_s(aux, aux2);
	}

	len = wcslen(aux);
	writeLine(aux, line++, len);

	len = swprintf(aux, (size_t)WIDTH, L"partial solution cost:%d", path.size());
	writeLine(aux, line++, len);


}

void printGrid(int grid[N][N], vector<point>& path, int rowg, int colg, const int mindist,  const int moves ,const int sol,int message=0)
{
	WCHAR aux[WIDTH] = { 0 };
	WCHAR aux2[WIDTH] = { 0 };

	int len = 0;
	int line = 0;

	printHeaderEx(line);
	printPath(path, line);

	len = swprintf(aux, (size_t)WIDTH, L"");
	writeLine(aux, line++, len);
	len = swprintf(aux,(size_t)WIDTH,L"row:%d col:%d",rowg,colg);
	writeLine(aux, line++, len);
	len = swprintf(aux, (size_t)WIDTH, L"best solution cost:%d solutions:%d moves:%d", mindist, sol,moves);
	writeLine(aux, line++, len);
	len = swprintf(aux, (size_t)WIDTH, L"---------------------------------------------------------------------------------------------------------------");
	writeLine(aux, line++, len);
	len = swprintf(aux, (size_t)WIDTH, L"");
	writeLine(aux, line++, len);
	len = swprintf(aux, (size_t)WIDTH, L"");
	writeLine(aux, line++, len);

	int cnt = 2;
	
	for (int row = 0; row < N; row++)
	{
		len=swprintf(aux, (size_t)WIDTH, L"row#%d--->  ",row);
		
		for (int col = 0; col < N; col++) {

			if (row == rowg && col == colg)
			{
				if (grid[row][col] > 9)
					swprintf(aux2, (size_t)WIDTH, L"*%d*   ", grid[row][col]);
				else
					swprintf(aux2, (size_t)WIDTH, L"*0%d*   ", grid[row][col]);
				wcscat_s(aux, aux2);
			}
			else if (grid[row][col] == 0)
			{
				swprintf(aux2, (size_t)WIDTH, L"--     ");
				wcscat_s(aux, aux2);
			}
			else if (grid[row][col] == -1)
			{
				swprintf(aux2, (size_t)WIDTH, L"++     ");
				wcscat_s(aux, aux2);
			}
			else
			{
				if(grid[row][col]>9)
					swprintf(aux2, (size_t)WIDTH, L"%d     ", grid[row][col]);
				else
					swprintf(aux2, (size_t)WIDTH, L"0%d     ", grid[row][col]);
				wcscat_s(aux, aux2);
			}

		}
		len = wcslen(aux);
		writeLine(aux, line++, len);

	}
	len = swprintf(aux, (size_t)WIDTH, L"---------------------------------------------------------------------------------------------------------------");
	writeLine(aux, line++, len);

	memset(aux, 0, (size_t)WIDTH);
	memset(aux2, 0, (size_t)WIDTH);
	swprintf(aux, (size_t)WIDTH, L"col# ");

	for (int col = 0; col < N; col++)
	{
		swprintf(aux2, (size_t)WIDTH, L"      %d",col);
		wcscat_s(aux, aux2);
	}

	len = wcslen(aux);
	writeLine(aux, line++, len);

	switch (message) 
	{
		case  2:
		{
			len = swprintf(aux, (size_t)WIDTH, L" Best solution found! cost:%d", path.size());
			writeLine(aux, line++, len);
			break;

		}
		case  1:
		{
			len = swprintf(aux, (size_t)WIDTH, L"solution found! cost:%d", path.size());
			writeLine(aux, line++, len);
			break;

		}
		
		case  -1:
			{
				len = swprintf(aux, (size_t)WIDTH, L"backtrack:[%d,%d]", rowg, colg);
				writeLine(aux, line++, len);
				break;

			}
		default:
			{
				len = swprintf(aux, (size_t)WIDTH, L"");
				writeLine(aux, line++, len);
				break;
			}
	}
	drawConsole();
}

bool isfeasable(int grid[N][N], point& origin)
{
	if (origin.x >= 0 && origin.y >= 0 &&
		origin.x < N &&  origin.y < N  &&
		grid[origin.x][origin.y] == 0 &&
		lookup[origin.x][origin.y] != -1)
		return true;

	return false;
}

void minimalpath2(int grid[N][N], point& dest, point& origin, vector<point>& path, vector<point>& bestsolution,int& moves,int& mindist, int& sol)
{


	lookup[origin.x][origin.y] = -1;
	path.push_back(origin);
	grid[origin.x][origin.y] = path.size();
	moves++;
	
	printGrid(grid, path, origin.x, origin.y, mindist,moves,sol);

	if ((int) path.size() > mindist)
	{
		lookup[origin.x][origin.y] = 0;
		grid[origin.x][origin.y] = 0;

		path.pop_back();

		return;
	}

	if (dest.x == origin.x&& dest.y == origin.y)
	{
		
		int message = 1;
		
		if ((int)path.size() < mindist)
		{
			mindist = path.size();
			bestsolution = path;
			message = 2;
		}
		
		printGrid(grid, path, origin.x, origin.y, mindist, moves, sol, message);

		lookup[origin.x][origin.y] = 0;
		grid[origin.x][origin.y] = 0;

		sol++;
		path.pop_back();
		return;
	}


	for (int index=0;index<4;index++)
	{
		point candidate = { 0 };

		candidate.x = origin.x + movem4[index][0];
		candidate.y = origin.y + movem4[index][1];
		if (isfeasable(grid, candidate))
			minimalpath2(grid, dest, candidate, path,bestsolution,moves,mindist,sol);
	}
	
	lookup[origin.x][origin.y] = 0;
	grid[origin.x][origin.y] = 0;
	moves++;
	path.pop_back();
	
	
	printGrid(grid, path, origin.x, origin.y, mindist, moves,sol,-1);



}

void restoreBestSolution(vector<point>& bestSolution, int grid[N][N])
{
	int cnt = 1;
	for (vector<point>::iterator t = bestSolution.begin(); t != bestSolution.end(); ++t,cnt++)
		grid[t->x][t->y] = cnt;
}
int main(void)
{
	initializeConsole();
	int line = 0;


	
	int grid[N][N] = { {-1, -1, -1, -1, 0, -1, -1, -1, -1},
						{-1, -1, -1, 0, 0, -1, -1, -1, -1},
						{-1, -1, -1, -1, 0, -1,-1, -1, -1},
						{-1, -1, -1, 0, 0, -1, -1, -1, -1},
						{-1, 0, 0, -1, 0, 0, 0, 0, -1},
						{ 0, 0, 0,  0, 0, -1, -1, 0,  0},
						{ 0,-1, -1, -1, 0, -1, -1, -1, 0},
						{0, 0, -1, -1, -1, -1, -1, -1, 0},
						{0, 0, 0, 0, 0, -1, -1, -1, 0} };
	
	vector <point> path;
	vector <point> bestsolution;
	int mindist = 9999;
	int moves = 0;
	int sol = 0;
	
	point orig = point{ 8,0 };
	point dest = point{ 8,8 };

	printGrid(grid, bestsolution, dest.x, dest.y, mindist, moves, sol);


	Sleep(5000);

	minimalpath2(grid, dest, orig, path, bestsolution,moves,mindist,sol); 
	restoreBestSolution(bestsolution, grid);
	printGrid(grid, bestsolution, dest.x, dest.y, mindist, moves,sol);

	Sleep(20000);

	return 0;
}
