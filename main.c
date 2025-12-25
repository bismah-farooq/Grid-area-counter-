/* Name: Bismah Farooq
   Date: 10/07/2025
   Assignment #3 - Grid Area Counter using Depth First Search implemented with a linked stack.
*/

#include <stdio.h>
#include <stdlib.h>

/* Structure: Point
Represents a location in the grid that will be placed on the stack.
Id[0]: row index
Id[1]: column index
next: pointer to the next Point node in the stack
*/
typedef struct point{
    int Id[2];
    struct point *next;
} point;
/* Structure: Stack
Represents a Stack data structure to store Point objects in LIFO order.
top: pointer to the Point node currently at the top of the stack.
*/
typedef struct stack{
    point *top;
} stack;
/* Function: push
Adds a new Point object to the top of the stack.
struct Stack *stack - [pointer to the stack to push]
int r - [row]
int c - [column]
*/
void push(struct stack *stack, int r, int c) {
    point *node = (point *)malloc(sizeof(point));
    if (!node) {
        fprintf(stderr, "ERROR - out of memory.\n");
        exit(1);
    }
    node->Id[0] = r;
    node->Id[1] = c;
    node->next = stack->top;
    stack->top = node;
}
/* Function: pop
Removes and deallocates the Point object from the top of the stack.
struct Stack *stack - pointer to the stack, the top Point node will be removed.
int *retloc - return parameter - retloc[0] receives the row index, and retloc[1] receives the column index.
*/
void pop(struct stack *stack, int *retloc) {
    if (stack->top == NULL) {
        fprintf(stderr, "ERROR - pop on empty stack.\n");
        exit(1);
    }
    point *node = stack->top;
    retloc[0] = node->Id[0];
    retloc[1] = node->Id[1];
    stack->top = node->next;
    free(node);
}
/* Function: print_grid
Displays the contents of the grid in a matrix format.
char **grid - [fill in your documentation here]
int rows - total number of rows in the grid
int cols - total number of columns in each row of the grid
*/
void print_grid(char **grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

// it reads the grid from the text file
int main()
{
    //open file
    FILE *fptr = fopen("grid.txt", "r");
    int rows, cols;
    char **grid;
    if(fptr != NULL) {
        //get rows & cols from file
        char c;
        fscanf(fptr, "%d%d%c", &rows, &cols, &c);
        //dynamically allocate 2D array
        grid = (char**)malloc(rows * sizeof(char*));
        if (!grid) {
            fprintf(stderr, "ERROR - out of memory\n");
            fclose(fptr);
            return 1;
        }
        for (int i = 0; i < rows; i++) {
            grid[i] = (char*)malloc(cols * sizeof(char));
            if (!grid[i]) {
                fprintf(stderr, "ERROR - out of memory\n");
                fclose(fptr);
                return 1;
            }
        }
        //read in grid
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j <= cols; j++) {
                char ch = fgetc(fptr);
                if(ch != '\n') {
                    grid[i][j] = ch;
                }
            }
        }
    } else {
        printf("ERROR - cannot open file.\n");
    }
    fclose(fptr);
    
    //display the grid
    printf("Grid (%d x %d):\n", rows, cols);
    print_grid(grid, rows, cols);

    //initialize stack
    struct stack stack;
    stack.top = NULL;
    
    //traverse the grid to find initial 'o' for each area
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    int area_id = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'o') {
                area_id++;
                int count = 0;

                //repeat while there is still items on the stack
                push(&stack, i, j);
                grid[i][j] = '*';
                while (stack.top != NULL) {

                    //pop an item from the stack
                    int cur[2];
                    pop(&stack, cur);
                    int r = cur[0], c2 = cur[1];
                    count++;

                    //check neighboring positions for 'o's and place them on the stack
                    //note: you should also make sure you're not going out of bounds
                    for (int k = 0; k < 4; k++) {
                        int nr = r + dr[k];
                        int nc = c2 + dc[k];
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 'o') {
                            push(&stack, nr, nc);
                            grid[nr][nc] = '*';
                        }
                    }
                }
                //display result of each area
                printf("Area %d = %d\n", area_id, count);
            }
        }
    }
    //clean up - free everything that was allocated on the heap
    while (stack.top != NULL) {
        int dummy[2];
        pop(&stack, dummy);
    }
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
