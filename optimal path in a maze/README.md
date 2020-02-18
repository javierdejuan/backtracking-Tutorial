
# Finding optimal path in a Maze

In [finding path in a maze](https://github.com/javierdejuan/backtracking-Tutorial/tree/master/solving%20a%20maze) we have shown how backtracking works in a simple problem. However, the solution found was not optimal, since we can find a path with less steps.
The purpose of this tutorial is to find the optimal solution using recursive calls and backtracking techniques. We will need to make some subtils modifications to our latter code.

<p align="center">
  <img width="520" height="390"  src="https://github.com/javierdejuan/backtracking-Tutorial/blob/master/optimal%20path%20in%20a%20maze/img/optimalpath2.gif">
</p>
<p align="center">
Finding Optimal Path in a Maze.
</p>

## General Idea

This is the pseudo code that solves the problem:

```c
void minimalpath2(int grid[N][N], point& dest, point& origin, vector<point>& path, vector<point>& bestsolution,int& moves,int& mindist)
{
	// we update our grid with the step number in its current location
  	// we also update a stl vector list which keeps track of the current path so far
	
  	lookup[origin.x][origin.y] = -1;
	path.push_back(origin);
	grid[origin.x][origin.y] = path.size();
	moves++;
	
  	// visualize so far
  	printGrid(grid, path, origin.x, origin.y, mindist,moves);

	
 	// check if we are done
 	if (dest.x == origin.x&& dest.y == origin.y)
 	{
		// we remove our last decision
		lookup[origin.x][origin.y] = 0;
		grid[origin.x][origin.y] = 0;
    		path.pop_back();

		// update best solution so far
    		if (path.size() < mindist)
		{
			mindist = path.size();
			bestsolution = path;
		}

		// keep searching
		return;
 	}

  	// we spawn out tree search here. 
  	// this for loop is going to ensure
  	// that we test all the possible 
  	// paths
  
	for (each_possible_candidate)
	{

		if (isfeasable(grid, candidate))
			minimalpath(grid, dest, candidate, path,bestsolution,moves,mindist);
	}
	
	// backtrack happens here:
  	// if no movement is possible, revert las decision
  
	lookup[origin.x][origin.y] = 0;
	grid[origin.x][origin.y] = 0;
	moves++;
	path.pop_back();

}


```
This time, our lookup table must work in a different way. When a solution is found, we need to backtrack until a new feasable movement is found. So, we need to restore last decisions until a new branch of the tree is found. Unfortunatly, we will recompute sub-solutions, but this is the price we need to pay to get to the optimal solution.
The backrracking xbprocess is shown in the following sequence:


## Heuristic Prune

An optimization to previous pseudo-code can be done. Notice when a partial solution yields a cost (number of steps) higher than our actual optimal solution, we can stop its calculation process.
This can be done inserting this piece of code before spawing the combination tree again:

``` C
if (path.size() > mindist)
{
	lookup[origin.x][origin.y] = 0;
	grid[origin.x][origin.y] = 0;
	path.pop_back();
	return;
}
```
