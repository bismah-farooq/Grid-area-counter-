# Grid Area Counter (C Program)

## Name
**Bismah Farooq**

---

## Description
This program implements a **Grid Area Counter** using **Depth First Search (DFS)** in C.  
It analyzes a two-dimensional grid and counts the size of connected regions (areas) by exploring neighboring cells.

The program uses a **stack-based DFS approach** to traverse the grid and ensures that each cell is visited only once.

---

## Features
- Uses Depth First Search (DFS)
- Stack-based traversal
- Counts connected areas in a grid
- Marks visited cells to avoid repetition
- Efficient and clear implementation
- Console-based output

---

## How the Program Works
1. A grid is stored in memory.
2. DFS begins at an unvisited cell.
3. Neighboring cells are explored using a stack.
4. Each visited cell is marked.
5. The size of each connected area is counted.
6. The final area count is displayed.

---

## Sample Output
```text
Grid Area Counter
Total connected area size: 12
```

## Compilation and Execution 
To compile and run the program using a terminal:
```text
gcc main.c -o grid_area_counter
./grid_area_counter
```

## Notes
* The program avoids revisiting grid cells by marking them as visited
* DFS traversal is implemented using a stack
* Designed for educational purposes to demonstrate graph traversal on grids

