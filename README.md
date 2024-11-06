In order to run this file use following command:

### for bfs_maze_solver ###
gcc -o bfs_maze_solver bfs_maze_solver.c queue.c
./bfs_maze_solver 

### for dfs_maze_solver ###
gcc -o dfs_maze_solver dfs_maze_solver.c stack.c
./dfs_maze_solver 

### for GUI_BFS ###
gcc -o GUI_BFS GUI_BFS.c queue.c -lSDL2
./GUI_BFS 

### for GUI_DFS ###
gcc -o GUI_DFS GUI_DFS.c stack.c -lSDL2
./GUI_DFS 
