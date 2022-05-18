/*
Name: Jasmine Ngo
CS 230 Project 1
Multiple submissions but ended up turning it in late because of my revisions
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//declare the values of each direction to be passed around after translating from the player's input
//this will be used in the if statements when figuring out where the player can go and if it is a valid move
#define UP 3;
#define DOWN 4;
#define LEFT 5;
#define RIGHT 6;
#define UPLEFT 7;
#define UPRIGHT 8;
#define DOWNLEFT 9;
#define DOWNRIGHT 10;

struct Grid {
    struct Grid* up;
    struct Grid* down;
    struct Grid* left;
    struct Grid* right;
    struct Grid* upLeft;
    struct Grid* upRight;
    struct Grid* downLeft;
    struct Grid* downRight;
    int data; //keeps track of the number that was taken on the grid
    int used; //shows what grids have already been taken 
    char player; //allows the program to know who it is in the board 'P' or 'A'
};

//To initilize each grid in the board with its point value, takes in the board to initial each grid
void boardInit(struct Grid** boardPtr) {
        int i, j;

    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            struct Grid newGrid = {.data = '0', .player = '0', .up = NULL, .down = NULL, .left = NULL, .right = NULL, .upLeft = NULL, .upRight =  NULL, .downLeft = NULL, .downRight = NULL};
            boardPtr[i][j] = newGrid;
            if (i == 0 || i == 5 || j == 0 || j == 5) {
                boardPtr[i][j].data = 1;
                boardPtr[i][j].player = '1';
            }
            if (j > 0 && j < 5 && i > 0 && i < 5) {
                boardPtr[i][j].data = 2;
                boardPtr[i][j].player = '2';
            }
            if ((j == 2 || j == 3) && (i == 2|| i == 3)) {
                boardPtr[i][j].data = 3;
                boardPtr[i][j].player = '3';
            }
        }
    }
}

//To print the board for the user to see the initialization of the grid, takes in the board to print out what's in the board
void printBoard(struct Grid** boardPtr) {
    int i;
    int j;

    //print col
    for(i = 0; i <= 6; i++) {
        if (i == 0) {
            printf(" ");
        } else {
            printf("%2d", i);
        }
    }
    printf("\n");

    for(i = 0; i < 6; i++) {
        //print row
        printf("%d ", i+1);

        for(j = 0; j < 6; j++) {
            printf("%c ", boardPtr[i][j].player);
            }
            printf("\n");
    }
}

//To link the board with the data structure with the corresponding direction, takes in the board to link the directions in the board--allowing
//the board to know where each direction is based on i and j
void boardLink(struct Grid** boardPtr) {
    int i, j;

    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            //vertical conditions
            //check if we can go down first
            if (i < 5) {
                boardPtr[i][j].down = &boardPtr[i+1][j];
                //down left
                if (j > 0) {
                    boardPtr[i][j].downLeft = &boardPtr[i+1][j-1];
                }
                //down right
                if (j < 5) {
                    boardPtr[i][j].downRight = &boardPtr[i+1][j+1];
                }
            }
            //check if we can go up
            if (i > 0) {
                boardPtr[i][j].up = &boardPtr[i-1][j];
                //up left
                if (j > 0) {
                    boardPtr[i][j].upLeft = &boardPtr[i-1][j-1];
                }
                //up right
                if (j < 5) {
                    boardPtr[i][j].upRight = &boardPtr[i-1][j+1];
                }
            }
            //horizantal conditions
            //left
            if (j > 0) {
                boardPtr[i][j].left = &boardPtr[i][j-1];
            }
            //right
            if (j < 5) {
                boardPtr[i][j].right = &boardPtr[i][j+1];
            }
        }
    }
}

//Function to get the player's input and get ready to disect it for the distance and direction.
//checking byte leaks and seeing what the player's next move is
char* getMove() { 
    char* move = NULL;
    size_t bufferSize = 14;
    move = malloc(bufferSize);
    printf("Enter a move:");
    //so there is no segmentation fault
    int bytes;
    bytes = getline(&move, &bufferSize, stdin);
    return move;
}

//To physically move to the players desired postion on the board
//takes in the player to move on the board, the direction and distance to know where to go, the points to keep track, and the playertype to understand
//if the position that it changed to is 'P' or 'A'
//returns an integer to see if it was successful
int boardMove(struct Grid** player, int** points, int playerType, int direction, int distance) { 
    int i = 0;
    //to know the before and after the player moves
    struct Grid** position = player;
    struct Grid** preposition;
    //to keep track of points
    int* temp = *points;
    while (distance >= 0 && (*position) != NULL) {
        (*position)->player = '.';
        (*position)->used = 1;
        distance =  distance - 1;
        preposition = position;

        //going through each direction to see where the player's desired move is.
        if(direction == 3) {
            position = &(*position)->up;
        } else if(direction == 4) {
            position = &(*position)->down;
        } else if(direction == 5) {
            position = &(*position)->left;
        } else if(direction == 6) {
            position = &(*position)->right;
        } else if(direction == 7) {
            position = &(*position)->upLeft;
        } else if(direction == 8) {
            position = &(*position)->upRight;
        } else if(direction == 9) {
            position = &(*position)->downLeft;
        } else if(direction == 10) {
            position = &(*position)->downRight;
        }
    }

    //assigning the player's marker at that grid
    if (playerType) {(
        *preposition)->player = 'P';
    }else {
        (*preposition)->player = 'A';
    }
    ///track points
    for (i = 0; i < 36; i++) {
        if (temp[i] == -1) {
            temp[i] = (*preposition)->data;
            break;
        }
    }
    //adding up the scores
    (*preposition)->data = (*preposition)->data + (*player)->data; 
    //player is now at that position
    *player = *preposition; 
    return 0;
}

//To check if there are anymore available spaces in the board for the player to move
//takes in the player to check the grids around the player and see if there are any moves left that the player can make
//returns an integer to see if it was successful
int playerMovesLeft(struct Grid ** player) { 
    if ((*player)->up != NULL && ((*player)->up->used == 0)) {
        return 1;
    } else if ((*player)->down != NULL && ((*player)->down->used == 0)) {
        return 1;
    } else if ((*player)->left != NULL && ((*player)->left->used == 0)) {
        return 1;
    } else if ((*player)->right != NULL && ((*player)->right->used == 0)) {
        return 1;
    } else if ((*player)->upLeft != NULL && ((*player)->upLeft->used == 0)) {
        return 1;
    } else if ((*player)->upRight != NULL && ((*player)->upRight->used == 0)) {
        return 1;
    } else if ((*player)->downLeft != NULL && ((*player)->downLeft->used == 0)) {
        return 1;
    } else if ((*player)->downRight != NULL && ((*player)->downRight->used == 0)) {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

//Allows the AI to choose the best possible direction based on the highest grid its postion is around on the board
//takes in the ai player to see where the player is at and see which grid is the best choice for them.
//returns an int for the direction its best move would be at
int bestAiMove(struct Grid** player) {
    int bestMove = 0;
    int direction = 0;
    if ((*player)->up != NULL && (*player)->up->data > bestMove && (*player)->up->used == 0) {
        bestMove = (*player)->up->data; 
        direction = 3;
    }
    if ((*player)->down != NULL && (*player)->down->data > bestMove && (*player)->down->used == 0) {
        bestMove = (*player)->down->data; 
        direction = 4;
    }
    if ((*player)->left != NULL && (*player)->left->data > bestMove && (*player)->left->used == 0) {
        bestMove = (*player)->left->data; 
        direction = 5;
    }
    if ((*player)->right != NULL && (*player)->right->data > bestMove && (*player)->right->used == 0) {
        bestMove = (*player)->right->data;
        direction = 6;
    }
    if ((*player)->upLeft != NULL && (*player)->upLeft->data > bestMove && (*player)->upLeft->used == 0) {
        bestMove = (*player)->upLeft->data; 
        direction = 7;
    }
    if ((*player)->upRight != NULL && (*player)->upRight->data > bestMove && (*player)->upRight->used == 0) {
        bestMove = (*player)->upRight->data; 
        direction = 8;
    }
    if ((*player)->downLeft != NULL && (*player)->downLeft->data > bestMove && (*player)->downLeft->used == 0) {
        bestMove = (*player)->downLeft->data; 
        direction = 9;
    }
    if ((*player)->downRight != NULL && (*player)->downRight->data > bestMove && (*player)->downRight->used == 0) {
        bestMove = (*player)->downRight->data; 
        direction = 10;
    }
    return direction;
}

//checks the direction that the player wants to go and sees if it is possible to move there
//based on if the grid has already been used or is being used.
//takes in the direstion and player to see if the player's desired direction is possible to make.
//if it is null, it cannot move
//returns an integer to see if it was successful, 0 = null 1 = successful in that direction
int nullMove(struct Grid** player, int direction) { 
    if (direction == 3) {
        if((*player)->up == NULL || (*player)->up->used == 1) {
            return 0;
        }
        return 1;
    } else if(direction == 4) {
        if((*player)->down == NULL || (*player)->down->used == 1){
            return 0;
        }
        return 1;
    } else if (direction == 5) {
        if((*player)->left == NULL || (*player)->left->used == 1) {
            return 0;
        }
        return 1;
    } else if (direction == 6) {
        if((*player)->right == NULL || (*player)->right->used == 1) {
            return 0;
        }
        return 1;
    } else if (direction == 7) {
        if((*player)->upLeft == NULL || (*player)->upLeft->used == 1) {
            return 0;
        }
        return 1;
    } else if (direction == 8) {
        if((*player)->upRight == NULL || (*player)->upRight->used == 1) {
            return 0;
        }
        return 1;
    } else if (direction == 9) {
        if((*player)->downLeft == NULL || (*player)->downLeft->used == 1) {
            return 0;
        }
        return 1;
    } else if (direction == 10) {
        if((*player)->downRight == NULL || (*player)->downRight->used == 1) {
            return 0;
        }
        return 1;
    }
    return 0;
}

//To take the input of the player and split it to extract the direction and distance the player wants to go
//takes in the players input to see where the player wants to move, the players ptr position to move the their position into moveBoard, and
//points to keep track the player's score.
//returns an int for success
int playersMove(char* move, struct Grid** humanPtr, int* points) { 
//Take the direction from the player's input, stops at white line to ge the player's distance number next
    char* strDir = strtok(move, " "); //gets first string
    char* strDis = strtok(NULL, "\0"); //gets second string
    //disect the input to see where the player wants to go
    int distance;
    if(strcmp(strDis, "1\n") == 0) {
        distance = 1;
    } else if(strcmp(strDis, "2\n") == 0) {
        distance = 2;
    } else if(strcmp(strDis, "3\n") == 0) {
        distance = 3;
    } else if(strcmp(strDis, "4\n") == 0) {
        distance = 4;
    } else if(strcmp(strDis, "5\n") == 0) {
        distance = 5;
    } else{
        distance = -1;
    }

    int direction;

     if(strcasecmp(strDir, "up") == 0) {
        direction = 3;
    } else if(strcasecmp(strDir, "down") == 0) {
        direction = 4;
    } else if(strcasecmp(strDir, "left") == 0) {
        direction = 5;
    } else if(strcasecmp(strDir, "right") == 0) {
        direction = 6;
    } else if(strcasecmp(strDir, "upleft") == 0) {
        direction = 7;
    } else if(strcasecmp(strDir, "upright") == 0) {
        direction = 8;
    } else if(strcasecmp(strDir, "downleft") == 0) {
        direction = 9;
    } else if(strcasecmp(strDir, "downright") == 0) {
        direction = 10;
    } else {
        direction = -1;
    }

    if (distance == -1 || direction == -1) { 
        return 0;
    }else {
        if (nullMove(humanPtr, direction) != 1) {
            return 0;
        }
        boardMove(humanPtr, &points, 1, direction, distance);
        return 1;  
    }
    return 1;
}

//To move the AI 
//Takes in the aPtr to see where the AI is at and to move it when passing it into the bestAiMove. It also takes in the aPoints to 
//keep track of the AI's points after every move
void aisMove(struct Grid** aPtr, int* aPoints) { 
    //choose best direction
    int direction = bestAiMove(aPtr); 
    //choose random number between 1-5 for the distance
    int randomDistance;
    randomDistance = rand() % 5;
    boardMove(aPtr, &aPoints, 0, direction, 1);
}

//Slowly ends the game with the last few turns and shows the game results to the player by adding up the scores
//Takes in the pPtr and aPtr to see where each player is at on the board and analyze if there are any moves left. 
//Also takes in pPoints and aPoints to count the number of points that were achieved by each player.
//boardPtr is also passed to be able to print the physical board during the last few turns.
void gameResults(struct Grid* pPtr, struct Grid* aPtr, int* pPoints, int* aPoints) {
    printf("\nYour score: %d\n", pPtr->data);
        for (int i = 0; i < 36; i++) {
            if (pPoints[i] == -1) {
                break;
            }
            printf("%d ", pPoints[i]);
        }
        printf(" = %d\n", pPtr->data);
        printf("AI's score: %d\n", aPtr->data);
        for (int i = 0; i < 36; i++) {
            if (aPoints[i] == -1) {
                break;
            }
            printf("%d  ", aPoints[i]);
        }
        printf(" = %d\n", aPtr->data);
}

//To declare the winner of the game. Takes in the pointers of each player and their points
//to pass into the gameResults function and compare--declaring the winner of the game after
//adding the points
void declareWinner(struct Grid* pPtr, struct Grid* aPtr, int* pPoints, int* aPoints) {
     if ((pPtr->data) > (aPtr->data)) { //compare added up scores
        gameResults(pPtr, aPtr, pPoints, aPoints);
        printf("You win!\n");
    }
    else if ((aPtr->data) == (pPtr->data)) {
        gameResults(pPtr, aPtr, pPoints, aPoints);
        printf("Tie!\n");
    }
    else {
        gameResults(pPtr, aPtr, pPoints, aPoints);
        printf("You lose!\n");
    }
}

int main(int argc, char* argv[]) {
    //creation of the board pointer
    struct Grid** boardPtr;
    //to decide which players turn it is
    int playerTurn = 1;

    //initializes the first 6 pointers of the board
    int i;
    boardPtr = malloc(sizeof(struct Grid*)*6);
    for (i = 0; i < 6; i++) {
        boardPtr[i] = malloc(sizeof(struct Grid)*6);
    }
    boardInit(boardPtr);
    boardLink(boardPtr);

    //set the position of each player as a pointer for the board
    struct Grid* pPtr = &(boardPtr[0][0]);
    pPtr->player = 'P'; 
    pPtr->used = 1;
    pPtr->data = 1;
    struct Grid* aPtr = &(boardPtr[5][5]);
    aPtr->player = 'A';
    aPtr->used = 1;
    aPtr->data = 1;

    //To keep track of points
    int* pPoints = malloc(sizeof(int)*36);
    int* aPoints = malloc(sizeof(int)*36);
    for (i = 0; i < 36; i++) {
        pPoints[i] = -1;
        aPoints[i] = -1;
    }

    printf("Hey, that's my fish!\n");
    printBoard(boardPtr);
    while ((playerMovesLeft(&pPtr) == 1) && (playerMovesLeft(&aPtr) == 1)) {
        if (playerTurn == 1) { 
            char* input = getMove();
            //get players move and see if it is a valid move
            if (playersMove(input, &pPtr, pPoints) != 1) {
                //if not try again
                printf("invalid move! try again!\n");
                //free malloc to get a new input
                free(input);
                continue;
            }
            else {
                printBoard(boardPtr);
                printf("Your score: %d, AI's score: %d \n", pPtr->data, aPtr->data);
                playerTurn = 0; //switches to the next player's turn
            }   
            //free malloc for the next time the player need to put in their move
            free(input);
        }
        else { 
            aisMove(&aPtr, aPoints);
            printBoard(boardPtr);
            printf("Your score: %d, AI's score: %d \n", pPtr->data, aPtr->data);
            playerTurn = 1;
        }
    }

    //if one player is out of moves, the other continues until they are all out of moves
    while (playerMovesLeft(&pPtr) == 1) { 
        printf("AI can't move! Enter a move!\n");
        printBoard(boardPtr);
        printf("Your score: %d, AI's score: %d\n", pPtr->data, aPtr->data);
        char* input = getMove();
        if (playersMove(input, &pPtr, pPoints) != 1) {
            printf("invalid move! try again!");
            free(input);
            continue;
        }
        free(input);
    }

    while (playerMovesLeft(&aPtr) == 1) {
        printf("You can't move anymore! AI's turn!\n");
        aisMove(&aPtr, aPoints);
        printBoard(boardPtr);
        printf("Your score: %d, AI's score: %d\n", pPtr->data, aPtr->data);
    }

    declareWinner(pPtr, aPtr, pPoints, aPoints);

    for (i = 0; i < 6; i++) {
        free(boardPtr[i]);
    }
    free(boardPtr);
    free(aPoints);
    free(pPoints);
    return 0;
}