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
4.1) Mark this cell as visited.
4.2) Store its father (the current pivot)
5) Pop your pivot cell from the queue
6) Select next pivot from the queue
7) Repeat from 3) until you find your destination
7bis) If destination cannot be reached, then the queue empties.

Once your Connection Matrix is filled, iterate through it and store each step in a vector.



