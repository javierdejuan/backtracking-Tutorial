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
  <img width="520" height="390"  

   src="https://github.com/javierdejuan/backtracking-Tutorial/blob/master/solving%20a%20maze/stack.PNG">
</p>
<p align="center">
Stack calls to solvemaze function.
</p>

This piece of code has a problem: We can search again an again the same sub-problems, which is time and ressources consumming. To avoid this, we need to check if the current candidate has already been tested by other branch.

## The Lookup Table



