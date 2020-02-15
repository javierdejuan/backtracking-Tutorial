# Solving a Maze

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

Moving to the East, for example, means adding 1 to current column location and so on.
Next, we have to check if the new candidate position in the Maze is feasable. 
In such case we move on and start the same process until the exit door is reached.

## Backtracking is your friend!

This is the pseudo-c-code that solves the problem:
```c
bool solvemaze(int grid[N][N],int current_row,int current_col)
{
  if(Exit_condition == true)
  {
    // we are done!
    return true;
  }
  else // path is not complete
  {
    for(each_possible_movement)                         // find a candidate
    {
      if(movement_is_feasable)                          // check if it is feasable
      {
        update_position();                              // update path
        
        if(solvemaze(grid,current_row,current_col))     // move to complete path
  
          return true;                                  // we have finished!
       
        else                                             // here, we have reach a blocking point, we can't move
          restore_position();                            // so, we have to revert the last decision
      }                                                  // end if
    }                                                    // end for
 }
 return false;                                          // backtracking is trigger here
}
```

To see how this pseudo-code works, let's dump the initial stack:

<p align="center">
  <img src="https://github.com/javierdejuan/backtracking-Tutorial/blob/master/solving%20a%20maze/backtracking.PNG">
</p>
<p align="center">
Stack calls to solvemaze function.
</p>

For each possible movement (indexed from 0 to 7) the code tests its feasability and then moves on to the next position. it is important to notice that the stack keeps in memory all the decisions taken so far and all the values of the local variables. Here is where the magic of backtracking comes to help us.
When ``` solvemaze(grid,current_row,current_col)``` returns false, all the candidate movements have been tried for a given position. The program then back jumps to previous decision taken and continue testing next possible movement. In this example, in line 19 the algorythm starts testing candidates for position [6,6]. Since no movements are valid, the algorythn triggers backtracking, and control is jumps back to the previous state described in line 18, trying next movement for cell [5,5] , in our case it is going to test the movement indexed with 2.
The tricky point here, is that you don't have to do extra work to memorize previous state, the stacks keeps for you all the information you need to restore previous decision.

However this piece of code has a problem: We can search again an again the same sub-problems (the algorythm may test candidates for a given cell position tested previously) which is time and ressources consumming. To avoid this, we need to check if the current candidate has already been tested by other branch.

## The Lookup Table

To solve this problem, we are going to add an extra condition for our feasability function. If the current candidate has already been tested we will skip to next candidate. This can be easily done through a lookup table which will be an array just like the grid.
We will then define a global array like this ``` int lookup[N][N]={0}```. When backtracks ocurrs we will write -1 in the current cell position. Last, in the feasibility function, we will check if the candidate has not already been tested.

## Final thoughts

Coding tricky algorithms using recursive calls and backtracking techniques can be very frustrating. Sometimes debug facilities given through you IDE does not help us so much since we lost the big picture. To make code experience pleasant and fun, i learnt in my early years as a programmer to add extra code to understand what is going on and to follow code execution. This is more than a logging feature to record exceptions and errors. Coding that way you will save time and will have a better understanding what you are coding (sometimes may be very different from your initial idea). Hope it helps.







