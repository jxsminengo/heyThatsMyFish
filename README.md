# heyThatsMyFish
Hey! That's my Fish!
Project 1 - CS230
By: Jasmine Ngo

    The game, "Hey, That's my Fish!", was created by first mallocing a 2D array and linking them together through the a struct Grid type called "newGrid". 
This way, the game would be able to identify the player, the points on that specific grid, the grid's use, and the direction of the following player. Malloc was also
used to keep track of the players points throughout the game, allowing functions to take in the points and change it when the players get to a different grid on the board.
The variables pPtr and aPtr allows the program to identify each player with a pointer--keeping track of where they are on the board. Before moving, the game starts off by seeing if there are any
available spots on the board. A while loop is set, as long as there are available spots left for the players to move to.
As long as the player had a non-NULL or unused grid around it, it was able to move around with the struct Grid directions. The game would check if there
were any used or NULL spots around the player with the function, nullMove. If the grid that the player waned to go to was NULL or used, the game would ask
the player to put in another move. The functions, nullMove and boardMove, was created with if statements taking in the values of the directions that were defined above and the distance. This allowed the game to understand where the player wants to go and where the player cannot go because it is being used or it is NULL.
The function, boardMove, takes in the pointers, temp for the points, position for the players current position, and preposition for when the player moves, the player's
previous position becomes the preposition--changing it to '.' and the current position as 'P' or 'A'.   
The uses of preposition and position allow us to have the player finally point to the new position in the end of the function.
    The board was constructed with the use of mallocing a 2D array. First, I declared the struct Grid for the boardPtr. I, then, malloced space for the 6 columns on the board. Within those 6 columns, 
I malloced another 6 rows. This allows the board to have 36 grids overall. After allocating space for the board, I initialized it by creating a new struct Grid called newGrid--allowing the boardPtr have
a row and column (i and j) to play with. With this, I called the function boardLink for the board to know where each direction is. For example, having the left pointer point at when boardPtr[i][j-1]. Once the whole board was linked up with each direction pointing at where it would be on the board, boardPtr was created. The boardPtr continues to be passed around each function to update the board after each move, updating the players' positions. Variable pointers allowed the game to keep track of each players points (pPoints and aPoints) and where each player is (pPtr and aPtr). These 
variable were passed to the functions playersMoveLeft to check the area around the pointer. It was also passed to the player and ai's moving functions to find space and also count points. This is put together
and counted in the function gameResults to declare the winner. 

    The AI was constructed by creating the functions, aiMove and bestAiMove. When it is the AI's turn, the program calls aiMove with the parameters aPtr(to see where the AI) and aPoints(to keep track of points).
aiMove takes in a direction by calling the function bestAiMove. bestAiMove allows the program to choose which direction the AI would get the highest score in. That way, there is a challenge for 
the player since the AI would know where to go. After deciding on which direction fit best with the AI, the variable randomDistance takes in a random number between 1 and 5. The number chosen is for the AI's chosen distance.
If the distance doesn't work, the function would run again until there is a valid move. 

    Through the movements of each player's turn, the board continues to get updated until there are no more moves to make. At the end of the game, the program counts up all the points with pPoint and aPoint, compares them,
and declares the winner with the results!
