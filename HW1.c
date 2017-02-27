/* 
 *
 */

//DON'T TOUCH
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//ALSO DON'T TOUCH ANY OF THE FOLLOWING
typedef enum status
{
	PLAYING,
	WON,
	LOST
} Status;

typedef enum type
{
	MINE,
	NOTAMINE
} Type;

typedef enum cover
{
	COVERED,
	UNCOVERED
} Cover;

//represents an individual square in the field 
typedef struct square
{
    int surroundingMines; //number of neighbors that are mines
    Cover C; //signifies the status of covered or uncovered
	Type T; //signifies the square being a mine or not
} Square;

typedef struct board
{
	int numRows; //the number of rows in the field of squares
	int numColumns; //the number of columns in the field of squares
	int numMines; //the total number of mines that are on the board
	int numRemaining; //the number of squares still covered that aren't mines
	Status s; //the status of the game currently being played
	Square** squares; //the actual board itself
} Board;

Board* randomizeBoard(int rows, int columns, int numMines);
void printBoard(Board* board);
void printUncoveredBoard(Board* board);
void updateBoard(Board* board, int x, int y);
int countMines(Board* board, int x, int y);
void freeBoard(Board* board);

//CAN TOUCH, BUT NOT ADVISED UNLESS YOU KNOW WHAT YOU'RE DOING
int main(int argc, char** argv) {
    srand(time(NULL));

	if(argc != 4)
	{
		printf("Correct usage: ./a.out <number of rows> <number of columns> <number of mines>\n");
		return -1;
	}

	Board* b = randomizeBoard(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	while(b->s == PLAYING)
	{
		printBoard(b);
		printf("\nSelect a row: ");
		int r;
		scanf("%d", &r);
		while(r < 0 || r > b->numRows - 1)
		{
			printf("Invalid entry. Try again: ");
			scanf("%d", &r);
		}

		printf("Select a column: ");
		int c;
		scanf("%d", &c);
		while(c < 0 || c > b->numColumns - 1)
		{
			printf("Invalid entry. Try again: ");
			scanf("%d", &c);
		}

		if(b->squares[r][c].C == UNCOVERED)
		{
			printf("\nThat square is already uncovered!\n");
		}
		else
		{
			updateBoard(b, r, c);
		}
	}

	if(b->s == WON) printf("\nYou won! Congrats!\n");
	else printf("\nYou hit a mine! Oh no!\n");
	printUncoveredBoard(b);

	freeBoard(b);
	return 0;
}



//BEGIN HW 1 REQUIRED FUNCTIONS

Board* randomizeBoard(int rows, int columns, int numMines)
{
    int i = 0, j = 0, laidMines = 0, row, col;
    
    // Initial board set up.
    Board* b = malloc(sizeof(Board));
    b->s = PLAYING;
    b->numRows = rows;
    b->numColumns = columns;
    b->numMines = numMines;
    b->numRemaining = (rows * columns) - numMines;
    
    // Allocating memory for the squares.
    Square** squares = (Square**)malloc(sizeof(Square*)*rows);
    for(i = 0; i < rows; i++) {
        squares[i] = (Square*)malloc(sizeof(Square)*columns);
    }
    
    // Initialize the square elements
    for(i = 0; i < rows; i++) {
        for(j = 0; j < columns; j++) {
            squares[i][j].T = NOTAMINE;
            squares[i][j].C = COVERED;
            squares[i][j].surroundingMines = -2;
        }
    }
    
    // Lay mines
    while(laidMines < numMines) {
        // Get a random (r,c) set
        row = rand() % rows;
        col = rand() % columns;
        if(squares[row][col].T == NOTAMINE) {
            squares[row][col].T = MINE;
            squares[row][col].surroundingMines = -1;
            laidMines++;
        }
    }
    
    b->squares = squares;
    
    countMines(b, 0, 0);
    
    return b;
    
}

/*
 
 If there are gonna be bugs, they'll probably be in here when dealing with 
 edge cases of the squares. When i is rows, and j is columns, then those numbers should
 always be >= 0. They should not exceed the numRows and numColumns inside board.
 
 */
int countMines(Board* board, int x, int y)
{
    int i = 0, j = 0, mineCt = 0;
    for(i = 0; i < board->numRows; i++) {
        for(j = 0; j < board->numColumns; j++) {
            if(board->squares[i][j].T == MINE) {
                board->squares[i][j].surroundingMines = -1;
            } else {
                /* Lil diagram to help me wrap my head around our playing grid
                 
                 1 2 3
                 4 X 5
                 6 7 8
                 
                 (-1,-1) (-1,+0) (-1,+1)
                 (+0,-1) (+0,+0) (+0,+1)
                 (+1,-1) (+1,+0) (+1,+1)
                 
                 */
                
                // 1
                if( ((i - 1 >= 0) && (j - 1 >=0)) && (board->squares[i-1][j-1].T == MINE)) {
                    mineCt++;
                }
                // 2
                if( (i - 1 >= 0) && (board->squares[i-1][j].T == MINE)) {
                    mineCt++;
                }
                // 3
                if( ((i - 1 >=0) && (j + 1 <= board->numColumns)) && (board->squares[i-1][j+1].T == MINE)) {
                    mineCt++;
                }
                // 4
                if( (j - 1 >= 0) && (board->squares[i][j-1].T == MINE)) {
                    mineCt++;
                }
                // 5
                if( (j + 1 <= board->numColumns) && (board->squares[i][j+1].T == MINE)) {
                    mineCt++;
                }
                // 6
                if( ((i + 1 < board->numRows) && (j - 1 >= 0)) && (board->squares[i+1][j-1].T == MINE)) {
                    mineCt++;
                }
                // 7
                if( (i + 1 < board->numRows) && (board->squares[i+1][j].T == MINE)) {
                    mineCt++;
                }
                // 8
                if( ((i + 1 < board->numRows) && (j + 1 <= board->numColumns)) && (board->squares[i+1][j+1].T == MINE)) {
                    mineCt++;
                }
                
                // Now that we counted the surrounding 8 squares (if they're there), add it to the middle square
                board->squares[i][j].surroundingMines = mineCt;
                mineCt = 0;
            }
        }
    }
    
    return 0;
}

void updateBoard(Board* board, int row, int column)
{
    // If you hit a mine, game over
    if(board->squares[row][column].T == MINE) {
        board->s = LOST;
        return;
    }
    
    // If there's no regular squares left, you win
    if(board->numRemaining <= 0) {
        board->s = WON;
        return;
    }
    
    if((board->squares[row][column].T == NOTAMINE) && (board->squares[row][column].surroundingMines >0)) {
        // Uncover the square
        board->squares[row][column].C = UNCOVERED;
        board->numRemaining--;
    }
    
    if((board->squares[row][column].T == NOTAMINE) && (board->squares[row][column].surroundingMines == 0)) {
        board->squares[row][column].C = UNCOVERED;
        
    }
    
}

void freeBoard(Board* board)
{
    int i = 0;
    for(i = 0; i < board->numRows; i++) {
        free(board->squares[i]);
    }
    free(board->squares);
    free(board);
}

//END REQUIRED FUNCTIONS



//DON'T TOUCH
void printBoard(Board* board)
{
	Square** squares = board->squares;

    int i, j;
    printf("\x1B[0m\n\n");
    printf("\x1B[0m\t   Columms:\n");

	printf("         ");
	for(i = 0; i < board->numColumns; i++)
	{
		printf("%d ", i);
	}
    printf("\n");
    for(i = 0; i < board->numRows; i++)
    {
        printf("\x1B[0m\nRow %d -> ", i);
        for(j = 0; j < board->numColumns; j++)
        {
            if(squares[i][j].C == COVERED)
            {
                printf("\x1B[0mx ");
            }
            else if (squares[i][j].surroundingMines == 0) 
            {
                printf("\x1B[32m%d ", squares[i][j].surroundingMines);
            } else {
                printf("\x1B[33m%d ", squares[i][j].surroundingMines);
            }
        }
    }
	printf("\n\n");
}

void printUncoveredBoard(Board* board)
{
	Square** squares = board->squares;

    int i, j;
    printf("\x1B[0m\n\n");
    printf("\x1B[0m\t   Columms:\n");
    printf("         ");
	for(i = 0; i < board->numColumns; i++)
	{
		printf("%d ", i);
	}
    printf("\n");
    for(i = 0; i < board->numRows; i++)
    {
        printf("\x1B[0m\nRow %d -> ", i);
        for(j = 0; j < board->numColumns; j++)
        {
            if(squares[i][j].T == MINE)
            {
                printf("\x1B[31mM ");
            }
            else if (squares[i][j].surroundingMines == 0) 
            {
                printf("\x1B[32m%d ", squares[i][j].surroundingMines);
            } else {
                printf("\x1B[33m%d ", squares[i][j].surroundingMines);
            }
        }
    }
	printf("\n\n");
}


