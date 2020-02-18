// sudoku2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <vector>

#include <algorithm>

#include <windows.h>

void clearScreen()
{
	// Get the Win32 handle representing standard output.
  // This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}

//typedef cliext::vector<int> Myvector;

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para  pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln


// A Backtracking program in C++ to solve Sudoku problem 
//#include <bits/stdc++.h> 
using namespace std;


// N is used for the size of Sudoku grid. 
// Size will be NxN 
#define N 9
int lookup[N][N] = { 0 };
struct point {
	int x;
	int y;
};



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
/* A utility function to print grid */
void printPath(vector<point>& path)
{
	cout << "path so far:" << endl;
	for (vector<point>::iterator t = path.begin(); t != path.end(); ++t)
	{
		std::cout << "[" << t->x << "," << t->y << "]";
	}
	cout << "\npartial solution cost:" << path.size() << endl;

}
void printGrid(int grid[N][N], vector<point>& path, int rowg, int colg, const int mindist = 0, const int moves = 0)
{
	//system("CLS");
	clearScreen();
	printHeader();
	printPath(path);

	cout << endl;
	cout << "row:" << rowg << " col:" << colg << endl;

	cout << "best solution cost:" << mindist << " moves:" << moves << endl;

	for (int col = 0; col < N; col++) {
		cout << "---------";

	}
	cout << endl;
	cout << endl;
	int cnt = 2;
	for (int row = 0; row < N; row++)
	{
		cout << "row# " << row << " - ";

		for (int col = 0; col < N; col++) {

			if(row==rowg&&col==colg)
				cout <<"*"<< grid[row][col] << "\t";
			else if (grid[row][col] == 0)
				cout << "--" << "\t";
			else if(grid[row][col]==-1)
				cout << "++" << "\t";
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

	cout << endl;

	//getchar();

}

// Driver Code 
int solvepath(int grid[N][N], int row, int col)
{

	int path = grid[0][0];
	int ct[N][N] = { 0 };


	for (int i = 0; i < N; i++)
		for (int j = 0; j <= i; j++)
		{
			ct[0][i] += grid[0][j];


		}

	for (int i = 1; i < N; i++)
		for (int j = 0; j <= i; j++)
		{
			ct[i][0] += grid[j][0];


		}

	for (int i = 1; i < row; i++)
		for (int j = 1; j < col; j++)
		{
			int num = max(ct[i][j - 1], ct[i - 1][j]);
			ct[i][j] = num + grid[i][j];
			path = ct[i][j];
		}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			cout << ct[i][j] << " ";

		}
		cout << endl;
	}

	return path;
}

int dist(int row, int col)
{
	return N - row + N - col;
}

const int movem[8][2] = { {1,1} ,{1,0} ,{1,-1},{0,-1}, {-1,-1},{-1,0},{-1,1} ,{0,1} };

bool optimalpath(int grid[N][N],vector<point>& v_path, int row, int col)
{
	bool bexit = true;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (grid[i][j] == 0)
				bexit = false;

		}

	if (bexit)
		return true;
	/*if (grid[N-1][N-1] > 0)
		return true;*/
	int i_c = 0;
	int i_move = 0;
	bool bfound = false;

	int minpath = 1000;

	for (int i = 0; i < 8; i++)
	{
		int row_c = movem[i][0] + row;
		int col_C = movem[i][1] + col;

		int path = 0;

		if ((row_c >= 0 && col_C >= 0) && (row_c < N && col_C < N) && grid[row][col] == 0 && grid[row_c][col_C] >= 5)
		{

			path = grid[row_c][col_C];
			if (path < minpath)
			{
				minpath = path;
				i_c = i;
				bfound = true;
			}

		}

	}
	if (bfound)
	{
		int row_c = movem[i_c][0] + row;
		int col_C = movem[i_c][1] + col;

		grid[row][col] = grid[row_c][col_C] + 5;
		printGrid(grid, v_path,row, col);
		getchar();

		for (int i = 0; i < 8; i++)
		{
			int row_n = movem[i][0] + row;
			int col_n = movem[i][1] + col;

			int path = 0;

			if ((row_n >= 0 && col_n >= 0) && (row_n < N && col_n < N) && grid[row_n][col_n] == 0)
			{

				if (optimalpath(grid,v_path, row_n, col_n))
					return true;

				//grid[row][col] = 0;




			}

		}


	}

	cout << "bactrack:" << row << ":" << col << endl;
	return false;
}

bool exitCondition(vector<point>& path, const point& dest)
{
	if (path.size())
	{
		point& current_point = path[path.size() - 1];
		if (current_point.x == dest.x&&current_point.y == dest.y)
			return true;
	}
	return false;
}
void findgradient(const point& dest, const point& current, point& gradient)
{
	
	gradient.x = dest.x - current.x;
	gradient.y = dest.y - current.y;

	if(gradient.x!=0)
		gradient.x = gradient.x > 0 ? 1 : -1;
	if(gradient.y!=0)
		gradient.y = gradient.y > 0 ? 1 : -1;

	
	return ;
}
bool sortbysec(const point &a,
	const point &b)
{
	return (a.y > b.y);
}
void findmovement(const point& gradient,vector<point>& mostvalue)
{
	
	for (int i = 0; i < 4; i++)
	{

		if (gradient.x == movem4[i][0] && gradient.y == movem4[i][1])
			mostvalue.push_back({ i,10 });
		else 
		{
			int prod = movem4[i][0] * gradient.x + movem4[i][1] * gradient.y;
			mostvalue.push_back({ i,prod });
		}
	}
	sort(mostvalue.begin(), mostvalue.end(), sortbysec);
	cout << "gradient:[" << gradient.x << "," << gradient.y << "]" << endl;
	for (vector<point>::iterator t = mostvalue.begin(); t != mostvalue.end(); ++t)
	
		cout << "[" << movem4[t->x][0] << ","<<movem4[t->x][1] << "]";

	//getchar();

	return;
}
bool isfeaseable(const int grid[N][N], const point& candidate) 
{
	bool retval = false;

	int row = candidate.x;
	int col = candidate.y;

	if (row < N && col < N &&
		row>=0 && col>=0 &&
		grid[row][col] ==0&&
		lookup[row][col] != -1)

		return true;

	return retval;
}

bool isfeasable(int grid[N][N], point& origin)
{
	if (origin.x >= 0 && origin.y >= 0 &&
		origin.x < N &&  origin.y < N  &&
		grid[origin.x][origin.y] ==0   &&
		lookup[origin.x][origin.y] != -1)
		return true;

	return false;
}
void minimalpath2(int grid[N][N], point& dest, point& origin,vector<point>& path)
{
	static int mindist = 9999;
	static vector<point> bestsolution;
	lookup[origin.x][origin.y] = -1;
	
	path.push_back(origin);
	grid[origin.x][origin.y] = path.size();

	//printPath(path);
	printGrid(grid, path, origin.x, origin.y,mindist);

	if (path.size() > mindist)
	{
		lookup[origin.x][origin.y] = 0;
		grid[origin.x][origin.y] = 0;

		path.pop_back();
		
		return;
	}
	
	if (dest.x == origin.x&& dest.y == origin.y)
	{
		cout << "path completed";

		//getchar();
		lookup[origin.x][origin.y] = 0;
		grid[origin.x][origin.y] = 0;

		if (path.size() < mindist)
		{
			mindist = path.size();
			bestsolution = path;
		}
		path.pop_back();
		return;
	}
	
	point gradient = { 0 };

	findgradient(dest, origin, gradient);

	vector<point> mostvalue;
	
	findmovement(gradient, mostvalue);
	
	for (vector<point>::iterator t = mostvalue.begin(); t != mostvalue.end(); ++t)
	{
		point candidate = { 0 };

		candidate.x = origin.x + movem4[t->x][0];
		candidate.y = origin.y + movem4[t->x][1];

		if (isfeasable(grid, candidate))
			minimalpath2(grid, dest, candidate,path);
	}
	
	
	printGrid(grid, path, origin.x, origin.y, mindist);

	cout << "backtracking:[" << origin.x <<","<< origin.y << "]" << endl;
	//getchar();
	
	lookup[origin.x][origin.y] = 0;
	grid[origin.x][origin.y] = 0;

	path.pop_back();

}

int main1()
{

	int grid[N][N] = { {0, 0, -1, -1, 0, -1, -1, 0, 0},
						{-1, 0, 0, 0, 0, -1, 0, 0, 0},
						{0, 0, -1, -1, 0, -1, 0, 0, -1},
						{0, 0, 0, 0, 0, -1, -1, -1, 0},
						{-1, 0, 0, -1, 0, 0, 0, 0, -1},
						{0, 0, 0, -1, 0, 0, -1, 0, 0},
						{0, -1, -1, -1, -1, -1, 0, -1, 0},
						{0, 0, 0, -1, -1, -1, -1, -1, 0},
						{0, 0, 0, 0, 0, -1, 0, -1, 0} };


	/*int grid[N][N]={   {0, 0, 0, 0 , 0 },
					  { 1, 0, 0, 1 , 0},
					  { 0, 0, 0, 0 , 1},
					  { 0, 1, 1, 0 , 0},
				  	};*/
	vector<vector <point>> lpath;

	vector <point> path;
	point orig = point{8,0};
	point dest = point{ 8,8};

	//copylooktable(grid, lookup);
	minimalpath2(grid,  dest, orig,path);
	getchar();

	return 0;
}

/*
*/
// This is code is contributed by rathbhupendra 


//#include <windows.h> 
//#include <stdio.h>
