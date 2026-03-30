/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



char maze[16][16]; //maze structure

typedef struct {
	int x;
	int y;
} Position; //global x and y coordinates

Position player;
Position police;

int manhattan(Position a, Position b){ //calculates manhattan distance
    return(abs(a.x-b.x))+(abs (a.y-b.y));
}

int isValid(int x, int y) { // checks if a coordinate is available 
	if(x >= 0 && x < 16 && y >= 0 && y < 16 && maze[x][y] != '|')


		return 1;
	else
		return 0;
}


void labrynth() { //maze and walls according to the instructions
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++) {
			maze[i][j] = '.';
		}

	maze[2][2]='|';
	maze[2][3]='|';
	maze[0][8]='|';
	maze[1][8]='|';
	maze[2][13]='|';
	maze[3][13]='|';
	maze[5][6]='|';
	maze[5][7]='|';
	maze[5][8]='|';
	maze[6][6]='|';
	maze[8][10]='|';
	maze[9][10]='|';
	maze[10][10]='|';
	maze[11][10]='|';
	maze[11][12]='|';
	maze[9][4]='|';
	maze[9][5]='|';
	maze[9][6]='|';
	maze[10][6]='|';
	maze[14][3]='|';
	maze[14][4]='|';
	maze[14][5]='|';
	maze[7][15]='E';


}
Position randomPosition() { //creates a random x,y Position in the maze
	Position p;
	do {
		p.x = rand() % 16;
		p.y = rand() % 16;
	} while (maze[p.x][p.y] == '|');
	return p;
}




void movePlayer() { //reads input from user and moves the thief if the Position is available
	char move;
	int movex=player.x;
	int movey=player.y;
	printf("Choose your move W A S D : ");
	scanf(" %c", &move);

	if (move == 'W' || move == 'w')
		movex= movex - 1;

	if (move == 'S' || move == 's')
		movex= movex + 1;

	if (move == 'A' || move == 'a')
		movey=movey - 1;

	if (move == 'D' || move == 'd')
		movey=movey +  1;

	if (isValid(movex,movey)) {
		player.x =movex;
		player.y =movey;
	}
}

void easyMode(){ //police moves randomly to a feasible square
    int validMoves[4];
    int count=0;
    
    if (isValid(police.x - 1, police.y)){
    validMoves[count] = 0;
    count++;
        
    }
     if (isValid(police.x + 1, police.y)){
    validMoves[count] = 1;
    count++;
        
    }
     if (isValid(police.x, police.y-1)){
    validMoves[count] = 2;
    count++;
        
    }
     if (isValid(police.x , police.y + 1)){
    validMoves[count] = 3;
    count++;
        
    }
        //chooses randomly between valid moves in the array
        int randomChoice = rand() % count; 
        int policemove = validMoves[randomChoice];

        if (policemove == 0)
        police.x -= 1;
        else if (policemove == 1) 
        police.x += 1;
        else if (policemove == 2) 
        police.y -= 1;
        else if (policemove == 3) 
        police.y += 1;
    
    }
    



void hardMode() { //police moves to the most reasonable square
     int candidates[4];    
    int minDistance= 10000;
   int count =0;
    
    int possiblex[] ={-1, 1, 0, 0}; // 
    int possibley[] ={0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int newx= police.x + possiblex[i]; //possible new x  coordinate
        int newy= police.y + possibley[i]; // possible new y coordinate
        
        if (isValid(newx, newy)) {
            Position nextPos = {newx, newy};
            int distance = manhattan(player, nextPos);
            
            if (distance < minDistance) {
                minDistance = distance;
                count = 0; 
                candidates[0] = i;
                count++ ;
            } 
            else if (distance == minDistance) {
                candidates[count] = i;
                count ++;
            }
        }
    }
    
    //chooses randomly between reasonable squares in the array
    int randomChoice = rand() % count; 
    int bestMove = candidates[randomChoice];
    police.x +=possiblex[bestMove];
    police.y +=possibley[bestMove];
    
}



void drawMaze() { //clears the screen and prints the labrynth
    system("clear"); 

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i == player.x && j == player.y)
                printf("T ");
            else if (i == police.x && j == police.y)
                printf("P ");
            else
                printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}
void placePlayers() { //places player, police and escape point
    Position escape = {7, 15};

    do {
        player = randomPosition();
    } while (maze[player.x][player.y] == 'E' || manhattan(player, escape) < 16);


    do {
        police = randomPosition();
    } while (
        maze[police.x][police.y] == 'E' || manhattan(player, police) < 16);
}



int main() {
	srand(time(NULL));
	int difficulty;
	char playAgain;
do { // it starts over until user do not wish to play again

    
    system("clear");
    printf("Select Difficulty Level:\n");
    printf("1. Easy \n");
    printf("2. Hard \n");
    printf("Choice: ");
    scanf("%d", &difficulty);
    int ingame = 1;
    labrynth();
    placePlayers();
    
    while(ingame){// It continues until player get caught, or escape
        drawMaze();
        
        
     movePlayer();
     if (player.x == 7 && player.y == 15) { 
        system("clear");
        printf("\n***  YOU WON!  ***\n");
        ingame = 0;
        break;
    }
     if (player.x == police.x && player.y == police.y) { //if player decides to suicide
        system("clear");
        printf("\n*** BUSTED! ***\n");
        ingame = 0;
        break;
    }
    
    if (difficulty == 1)
    easyMode();
    if (difficulty== 2) 
    hardMode();
    

    if (player.x == police.x && player.y == police.y) {
        system("clear");
        printf("\n*** BUSTED! ***\n");
        ingame = 0;
        break;
    }
    
    
    
   
        
        
    } 
    printf("\nDo you want to play again? (y/n): ");
    scanf(" %c", &playAgain);
    }
  while (playAgain == 'y' || playAgain == 'Y');
  system("clear");
  return 0;

}
