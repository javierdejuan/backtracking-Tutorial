### Solving a Maze

The purpose of this example is to find a path between an entry point and an exit point in a Maze.
The Maze, for simplicity is going to be represented as an NxN Matrix. We start at position [0,0] and we have to find a path until reaching position [8,8]. Cells numbered with 0 are passing cells and cells numbered with 1 are non-passing cells. Everytime we move into a new cell, this cell is labeled with a 3. 

<p align="center">
  <img width="520" height="390"  src="https://github.com/javierdejuan/backtracking-Tutorial/blob/master/solving%20a%20maze/solving%20a%20maze.gif">
</p>
<p align="center">
Soving a Maze Backtracking process.
</p>

## General idea

Given a position in the Maze, defined by it's row and col number, we have 8 possibilities to move on:
<p align="center">
North - North East - East - South East - South - South West - West - North West
  
</p>
