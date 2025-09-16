/*
	Description: The C program is designed to recreate a miniature 
	and simpler version of Monopoly called Minopoly through the command line.
	Programmed by: Rafael Enrico C. Hugo
	Last modified: December 4, 2022
	Version: 4.0
	Acknowledgements: 
	https://theasciicode.com.ar/ | Website of all ASCII codes 
								   and their equivalent characters
	
*/

/* Compile command to be used in the command line
gcc -Wall -std=c99 Minopoly.c -o Minopoly && Minopoly.exe
*/

//The standard input and output header file for C.
#include <stdio.h> 

/*This header file contains rand and srand functions which is used for rollDice()
	               Additionally it also contains system("cls") used for 
				   clearing the screen of previous iterations. Further, it also
				   contains fflush(stdin) to 'flush' or remove an unwanted input
				   especially for rollDice() and getGamemode().
*/
#include <stdlib.h>	

//Without time.h, makes use of time(NULL) so that every input for srand is different.
#include <time.h>

/*Windows.h contains Sleep() which I used to delay the increment-updating of 
							 the board
*/
#include <windows.h>

//List of function prototypes

//Functions that only display
void displayTitle();

void displayBalance(float balance1, float balance2);

void updateBoard(int propertyA, int propertyB, int propertyC, int propertyD, 
int propertyE, int propertyF, int propertyG, int propertyH, int propertyI,
int propertyJ, int propertyK, int propertyL, int propertyM, int propertyN, 
int propertyO, int tile0, int tile1, int tile2, int tile3, int tile4, int tile5,
int tile6, int tile7, int tile8, int tile9, int tile10, int tile11,
int tile12, int tile13, int tile14, int tile15, int tile16, int tile17,
int tile18, int tile19);

//Functions that change or return values
int getGamemode();

void changeValues(int dice, int *propertyValue, int *rentFee);

int rollDice();

void endGame(int balance, int player1, int *mode);

void jailCount(int *jail);

void checkDice(int *yesOrNo, int *tile0, int *tile1, int *tile2, int *tile3, 
int *tile4, int *tile5, int *tile6, int *tile7, int *tile8, int *tile9, 
int *tile10, int *tile11, int *tile12, int *tile13, int *tile14, int *tile15, 
int *tile16, int *tile17, int *tile18, int *tile19, int storedice1, int storedice2);

int isThereOwner(int property);

void payRent(float *balance1, float *balance2, int rentFee, int player1, int property,
int *yesOrNo);

int buyProperty(int *property, float *balance1, float *balance2, 
int propertyValue, int player1);

void displayRound(int dice, int player1, int maxdice, int yesOrNo,
int *jail1, int *jail2);

void collectGo(int storedice, float *balance, int *goCount, int maxdice);

//Main Function
int main()
{
	//Variable declarations
	int mode = 0;
	
	//Loop to return to title screen
	while (mode == 0)
	{
	int nDice, dice = 0, dice1 = 0, dice2 = 0, storedice1 = 0, storedice2 = 0; 
	int player1, yesOrNo = 0;
	int jail1 = 0, jail2 = 0;
	float balance1 = 10000000, balance2 = 10000000;
		
	int propertyA = 32, propertyB = 32, propertyC = 32, propertyD = 32; //Left properties
	int propertyE = 32, propertyF = 32, propertyG = 32, propertyH = 32; //Top properties
	int propertyI = 32, propertyJ = 32, propertyK = 32, propertyL = 32; //Right properties
	int propertyO = 32, propertyN = 32, propertyM = 32; //Bottom properties
	
	int tile0 = 32, tile1 = 32, tile2 = 32, tile3 = 32; 
	int tile4 = 32, tile5 = 32, tile6 = 32, tile7 = 32;
	int tile8 = 32, tile9 = 32, tile10 = 32, tile11 = 32; 
	int tile12 = 32, tile13 = 32, tile14 = 32;
	int tile15 = 32, tile16 = 32, tile17 = 32; 
	int tile18 = 32, tile19 = 32;
	
	int propertyValue = 0, rentFee = 0, owner;
	int goCount = 0;
		
	system("cls"); //Clears the screen
	
	displayTitle(); //Displays author and title
	
	mode = getGamemode(); //Gets the gamemode from the user
	
	//Conditional to prevent displaying the board if the game resets
	if (mode != 3 && mode != 0) 
	{
		updateBoard(propertyA, 
		propertyB, propertyC, propertyD, propertyE,
		propertyF, propertyG, propertyH, propertyI,
		propertyJ, propertyK, propertyL, propertyM,
		propertyN, propertyO,
		tile0, tile1, tile2, tile3, tile4, tile5,
		tile6, tile7, tile8, tile9, tile10, tile11,
		tile12, tile13, tile14, tile15, tile16, tile17,
		tile18, tile19);
		
		displayBalance(balance1, balance2);
	}
	
	//Loop used to keep the game going and to contain it all
	while (mode != 0 && mode != 3)
	{
		nDice = 0;
		player1 = 1;
		owner = 0;
		//Conditional statement to decide whether the player gets turn this round
		if (jail1 == 0 && mode != 0)
		{
		//Turn for Player one
		dice = rollDice(mode);
	
		dice1 += dice;
		
		//Loop to update board depending on the rolled dice.
		while (nDice <= dice && storedice1 <= dice1)
		{
		Sleep(500);
		
		checkDice(&yesOrNo,	&tile0, &tile1, &tile2, &tile3, &tile4, &tile5,
    	&tile6, &tile7, &tile8, &tile9, &tile10, &tile11,
    	&tile12, &tile13, &tile14, &tile15, &tile16, &tile17,
    	&tile18, &tile19, storedice1, storedice2);
    
    	updateBoard(propertyA, propertyB, propertyC, propertyD, propertyE,
		propertyF, propertyG, propertyH, propertyI,
		propertyJ, propertyK, propertyL, propertyM,
		propertyN, propertyO, tile0, tile1, tile2, tile3, tile4, tile5,
		tile6, tile7, tile8, tile9, tile10, tile11,
		tile12, tile13, tile14, tile15, tile16, tile17,
		tile18, tile19);
	
		displayBalance(balance1, balance2);
		
		displayRound(dice, player1, dice1, yesOrNo, &jail1, &jail2);
	
		collectGo(storedice1, &balance1, &goCount, dice1);
		nDice++;
		storedice1++;
		}
		storedice1--;
		
		//Property values and rent fees are changed here.
		changeValues(dice1, &propertyValue, &rentFee);
		
		//Switch statement for different properties and different dice states
		switch (dice1 % 20)
		{
		case 0:
			break;
		case 1:
			owner = isThereOwner(propertyA);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyA, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyA, &balance1, &balance2, propertyValue, player1);
			break;
		case 2:
			owner = isThereOwner(propertyB);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyB, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyB, &balance1, &balance2, propertyValue, player1);
			break;
		case 3:
			owner = isThereOwner(propertyC);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyC, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyC, &balance1, &balance2, propertyValue, player1);
			break;
		case 4:
			owner = isThereOwner(propertyD);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyD, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyD, &balance1, &balance2, propertyValue, player1);
			break;
		case 5:
			break;
		case 6:
			owner = isThereOwner(propertyE);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyE, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyE, &balance1, &balance2, propertyValue, player1);
			break;
		case 7:
			owner = isThereOwner(propertyF);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyF, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyF, &balance1, &balance2, propertyValue, player1);
			break;
		case 8:
			owner = isThereOwner(propertyG);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyG, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyG, &balance1, &balance2, propertyValue, player1);
			break;
		case 9:
			owner = isThereOwner(propertyH);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyH, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyH, &balance1, &balance2, propertyValue, player1);
			break;
		case 10:
			break;
		case 11:
			owner = isThereOwner(propertyI);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyI, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyI, &balance1, &balance2, propertyValue, player1);
			break;
		case 12:
			owner = isThereOwner(propertyJ);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyJ, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyJ, &balance1, &balance2, propertyValue, player1);
			break;
		case 13:
			owner = isThereOwner(propertyK);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyK, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyK, &balance1, &balance2, propertyValue, player1);
			break;
		case 14:
			owner = isThereOwner(propertyL);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyL, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyL, &balance1, &balance2, propertyValue, player1);
			break;
		case 15:
			dice1 = 5;
			storedice1 = 5;
			break;
		case 16:
			owner = isThereOwner(propertyM);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyM, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyM, &balance1, &balance2, propertyValue, player1);
			break;
		case 17:
			owner = isThereOwner(propertyN);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyN, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyN, &balance1, &balance2, propertyValue, player1);
			break;
		case 18:
			balance1 -= 1000000;
			break;
		case 19:
			owner = isThereOwner(propertyO);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyO, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyO, &balance1, &balance2, propertyValue, player1);
			break;
		}
		
		storedice1++;
    
		updateBoard(propertyA, propertyB, propertyC, propertyD, propertyE,
		propertyF, propertyG, propertyH, propertyI,
		propertyJ, propertyK, propertyL, propertyM,
		propertyN, propertyO, tile0, tile1, tile2, tile3, tile4, tile5,
		tile6, tile7, tile8, tile9, tile10, tile11,
		tile12, tile13, tile14, tile15, tile16, tile17,
		tile18, tile19);
		
		displayBalance(balance1, balance2);
	
		displayRound(dice, player1, dice1, yesOrNo, &jail1, &jail2);
		storedice1--;
		jailCount(&jail2);
		}
		
		//Function used to determine if the game will continue
		endGame(balance1, player1, &mode);
		
		nDice = 0;
		player1 = 0;
		owner = 0;
		//Conditional statement to decide whether the player gets turn this round
		if (jail2 == 0 && mode != 0)
		{
		//Turn for Player one
		dice = rollDice(mode);
	
		dice2 += dice;
		
		//Loop to update board depending on the rolled dice.
		while (nDice <= dice && storedice2 <= dice2)
		{
		Sleep(500);
	
		checkDice(&yesOrNo,	&tile0, &tile1, &tile2, &tile3, &tile4, &tile5,
    	&tile6, &tile7, &tile8, &tile9, &tile10, &tile11,
    	&tile12, &tile13, &tile14, &tile15, &tile16, &tile17,
    	&tile18, &tile19, storedice1, storedice2);
    
    	updateBoard(propertyA, propertyB, propertyC, propertyD, propertyE,
		propertyF, propertyG, propertyH, propertyI,
		propertyJ, propertyK, propertyL, propertyM,
		propertyN, propertyO, tile0, tile1, tile2, tile3, tile4, tile5,
		tile6, tile7, tile8, tile9, tile10, tile11,
		tile12, tile13, tile14, tile15, tile16, tile17,
		tile18, tile19);
		
		displayBalance(balance1, balance2);
	
		displayRound(dice, player1, dice2, yesOrNo, &jail1, &jail2);
	
		collectGo(storedice2, &balance2, &goCount, dice1);
		nDice++;
		storedice2++;
		}
		storedice2--;
		
		//Property values and rent fees are changed here.
		changeValues(dice2, &propertyValue, &rentFee);
	
		//Switch statement for different properties and different dice states
		switch (dice2 % 20)
		{
		case 0:
			break;
		case 1:
			owner = isThereOwner(propertyA);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyA, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyA, &balance1, &balance2, propertyValue, player1);
			break;
		case 2:
			owner = isThereOwner(propertyB);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyB, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyB, &balance1, &balance2, propertyValue, player1);
			break;
		case 3:
			owner = isThereOwner(propertyC);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyC, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyC, &balance1, &balance2, propertyValue, player1);
			break;
		case 4:
			owner = isThereOwner(propertyD);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyD, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyD, &balance1, &balance2, propertyValue, player1);
			break;
		case 5:
			break;
		case 6:
			owner = isThereOwner(propertyE);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyE, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyE, &balance1, &balance2, propertyValue, player1);
			break;
		case 7:
			owner = isThereOwner(propertyF);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyF, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyF, &balance1, &balance2, propertyValue, player1);
			break;
		case 8:
			owner = isThereOwner(propertyG);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyG, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyG, &balance1, &balance2, propertyValue, player1);
			break;
		case 9:
			owner = isThereOwner(propertyH);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyH, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyH, &balance1, &balance2, propertyValue, player1);
			break;
		case 10:
			break;
		case 11:
			owner = isThereOwner(propertyI);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyI, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyI, &balance1, &balance2, propertyValue, player1);
			break;
		case 12:
			owner = isThereOwner(propertyJ);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyJ, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyJ, &balance1, &balance2, propertyValue, player1);
			break;
		case 13:
			owner = isThereOwner(propertyK);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyK, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyK, &balance1, &balance2, propertyValue, player1);
			break;
		case 14:
			owner = isThereOwner(propertyL);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyL, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyL, &balance1, &balance2, propertyValue, player1);
			break;
		case 15:
			dice2 = 5;
			storedice2 = 5;
			break;
		case 16:
			owner = isThereOwner(propertyM);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyM, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyM, &balance1, &balance2, propertyValue, player1);
			break;
		case 17:
			owner = isThereOwner(propertyN);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyN, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyN, &balance1, &balance2, propertyValue, player1);
			break;
		case 18:
			balance2 -= 1000000;
			break;
		case 19:
			owner = isThereOwner(propertyO);
			if (owner == 1)
			payRent(&balance1, &balance2, rentFee, player1, propertyO, &yesOrNo);
			else
			yesOrNo = buyProperty(&propertyO, &balance1, &balance2, propertyValue, player1);
			break;
		}
	
		storedice2++;
    
		updateBoard(propertyA, propertyB, propertyC, propertyD, propertyE,
		propertyF, propertyG, propertyH, propertyI,
		propertyJ, propertyK, propertyL, propertyM,
		propertyN, propertyO, tile0, tile1, tile2, tile3, tile4, tile5,
		tile6, tile7, tile8, tile9, tile10, tile11,
		tile12, tile13, tile14, tile15, tile16, tile17,
		tile18, tile19);
	
		displayBalance(balance1, balance2);
	
		displayRound(dice, player1, dice2, yesOrNo, &jail1, &jail2);
		storedice2--;
		jailCount(&jail1);
		}
		
		//Function used to determine if the game will continue
		endGame(balance2, player1, &mode);
	}
	}
}
	//Spacer


/*
void displayTitle() is a function used to display the title and author of the
					project.
Pre-condition: None
*/
void displayTitle()
{
	printf("Welcome to Minipoly, a Machine Project created");
	printf(" by Rafael Enrico C. Hugo of S21B\n");
}

/*
int getGamemode() is a function used to select the gamemode.
Pre-condition: None
@returns the input mode out of the three available.
*/
int getGamemode()
{
	int mode;
		
	printf("To start, please choose a gamemode.");
	printf("\n[1] Play mode");
	printf("\n[2] Debug mode");
	printf("\n[3] Exit\n\n");
	scanf("%d", &mode);
	fflush(stdin);
	
	while (mode > 3 || mode < 1)
	{
		system("cls");
		printf("Enter a valid gamemode: ");		
		printf("\n[1] Play mode");
		printf("\n[2] Debug mode");
		printf("\n[3] Exit\n\n");
		scanf("%d", &mode);
		fflush(stdin);
	}
	
	return mode;
}

/*
int rollDice() is a function used to roll a dice from 1 to 6.***
Pre-condition: None
@param mode = Used to determine which dice is going to be used.
@returns the value of the random "six-sided" die or the input number between
         one and twenty.
*/
int rollDice(int mode)
{
	int prompt, dice;
	
	if (mode == 2)
	{
		printf("\n\nRoll the dice, choose a number from 1 to 20: ");
		scanf("%d", &dice);
		fflush(stdin);
		//Loop used for incorrect or invalid input.
		while (dice < 1 || dice > 20)
		{
			printf("Please enter a valid input: ");
			scanf("%d", &dice);
			fflush(stdin);
		}
	}
	else if (mode == 1)
	{
	printf("\n\nEnter any letter or number to roll the dice randomly from 1 to 6.\n");
	scanf("%d", &prompt);
	
	srand(time(NULL));
	dice = rand() % 6 + 1;
	}
	
	return dice;
}


/*
void checkDice() changes the value of each tile given the value of storedice.
				 Additionally, it also resets each tile while retaining the 
				 previous values.
Pre-condition: None
@param *tile0 to *tile19 = These are the tiles used for updateBoard(). These
						   are pointers because each one has to be updated for
						   each iteration.
@param storedice1 & storedice2 = This is where the dice from the previous turn
								 is stored and is used to hold the static position
								 of the player token
@param *yesOrNo = This value is simply reset in this function.
*/
void checkDice(int *yesOrNo,
int *tile0, int *tile1, int *tile2, int *tile3, int *tile4, int *tile5,
int *tile6, int *tile7, int *tile8, int *tile9, int *tile10, int *tile11,
int *tile12, int *tile13, int *tile14, int *tile15, int *tile16, int *tile17,
int *tile18, int *tile19, int storedice1, int storedice2)
{
	//Tiles are reset in these declarations. ASCII coding is used for easier
	//conversion for updateBoard()
	*tile0 = 32, *tile1 = 32, *tile2 = 32, *tile3 = 32; 
	*tile4 = 32, *tile5 = 32, *tile6 = 32, *tile7 = 32;
	*tile8 = 32, *tile9 = 32, *tile10 = 32, *tile11 = 32; 
	*tile12 = 32, *tile13 = 32, *tile14 = 32;
	*tile15 = 32, *tile16 = 32, *tile17 = 32; 
	*tile18 = 32, *tile19 = 32;
	*yesOrNo = 2;
	
	/*As the board is updated for each tile, storedice is used instead of dice
	since storedice is the one incrementing in the main function. It is also
	needed for storedice to be subjected to mod20 as there are only 20 tiles.
	*/
	storedice1 = storedice1 % 20;
	storedice2 = storedice2 % 20;
	
	
	/*Conditional statement if ever the two tokens are in the same tile. This 
	considers equality even if a player token just happens to pass by and 
	not exactly land on the tile
	*/ 
	if (storedice2 == storedice1 || storedice1 == storedice2)
	{
		switch (storedice1)
	{
		case 0:
			*tile0 = 51;
			break;
		case 1:
			*tile1 = 51;
			break;
		case 2:
			*tile2 = 51;
			break;
		case 3:
			*tile3 = 51;
			break;
		case 4:
			*tile4 = 51;
			break;
		case 5:
			*tile5 = 51;
			break;
		case 6:
			*tile6 = 51;
			break;
		case 7:
			*tile7 = 51;
			break;
		case 8:
			*tile8 = 51;
			break;
		case 9:
			*tile9 = 51;
			break;
		case 10:
			*tile10 = 51;
			break;
		case 11:
			*tile11 = 51;
			break;
		case 12:
			*tile12 = 51;
			break;
		case 13:
			*tile13 = 51;
			break;
		case 14:
			*tile14 = 51;
			break;
		case 15:
			*tile15 = 51;
			break;
		case 16:
			*tile16 = 51;
			break;
		case 17:
			*tile17 = 51;
			break;
		case 18:
			*tile18 = 51;
			break;
		case 19:
			*tile19 = 51;
			break;
	}
	}
	//Else statement if ever the storedice values are unequal
	else switch (storedice1)
	{
		case 0:
			*tile0 = 49;
			break;
		case 1:
			*tile1 = 49;
			break;
		case 2:
			*tile2 = 49;
			break;
		case 3:
			*tile3 = 49;
			break;
		case 4:
			*tile4 = 49;
			break;
		case 5:
			*tile5 = 49;
			break;
		case 6:
			*tile6 = 49;
			break;
		case 7:
			*tile7 = 49;
			break;
		case 8:
			*tile8 = 49;
			break;
		case 9:
			*tile9 = 49;
			break;
		case 10:
			*tile10 = 49;
			break;
		case 11:
			*tile11 = 49;
			break;
		case 12:
			*tile12 = 49;
			break;
		case 13:
			*tile13 = 49;
			break;
		case 14:
			*tile14 = 49;
			break;
		case 15:
			*tile15 = 49;
			break;
		case 16:
			*tile16 = 49;
			break;
		case 17:
			*tile17 = 49;
			break;
		case 18:
			*tile18 = 49;
			break;
		case 19:
			*tile19 = 49;
			break;
	}
	
	/*Conditional statement if ever the two tokens are in the same tile. This 
	considers equality even if a player token just happens to pass by and 
	not exactly land on the tile
	*/ 
	if (storedice2 == storedice1 || storedice1 == storedice2)
	{
		switch (storedice2)
	{
		case 0:
			*tile0 = 51;
			break;
		case 1:
			*tile1 = 51;
			break;
		case 2:
			*tile2 = 51;
			break;
		case 3:
			*tile3 = 51;
			break;
		case 4:
			*tile4 = 51;
			break;
		case 5:
			*tile5 = 51;
			break;
		case 6:
			*tile6 = 51;
			break;
		case 7:
			*tile7 = 51;
			break;
		case 8:
			*tile8 = 51;
			break;
		case 9:
			*tile9 = 51;
			break;
		case 10:
			*tile10 = 51;
			break;
		case 11:
			*tile11 = 51;
			break;
		case 12:
			*tile12 = 51;
			break;
		case 13:
			*tile13 = 51;
			break;
		case 14:
			*tile14 = 51;
			break;
		case 15:
			*tile15 = 51;
			break;
		case 16:
			*tile16 = 51;
			break;
		case 17:
			*tile17 = 51;
			break;
		case 18:
			*tile18 = 51;
			break;
		case 19:
			*tile19 = 51;
			break;
	}
	}
	//Else statement if ever the storedice values are unequal
	else switch (storedice2)
	{
		case 0:
			*tile0 = 50;
			break;
		case 1:
			*tile1 = 50;
			break;
		case 2:
			*tile2 = 50;
			break;
		case 3:
			*tile3 = 50;
			break;
		case 4:
			*tile4 = 50;
			break;
		case 5:
			*tile5 = 50;
			break;
		case 6:
			*tile6 = 50;
			break;
		case 7:
			*tile7 = 50;
			break;
		case 8:
			*tile8 = 50;
			break;
		case 9:
			*tile9 = 50;
			break;
		case 10:
			*tile10 = 50;
			break;
		case 11:
			*tile11 = 50;
			break;
		case 12:
			*tile12 = 50;
			break;
		case 13:
			*tile13 = 50;
			break;
		case 14:
			*tile14 = 50;
			break;
		case 15:
			*tile15 = 50;
			break;
		case 16:
			*tile16 = 50;
			break;
		case 17:
			*tile17 = 50;
			break;
		case 18:
			*tile18 = 50;
			break;
		case 19:
			*tile19 = 50;
			break;
	}
}


/*
void updateBoard() is the function used to display the board and all tile
				   and property variables. 
Pre-condition: None
@param tile0 - tile19 = The tiles are needed as they would make up each part 
						of the board where the player tokens are placed. 	
@param propertyA - propertyO = The properties are needed as they would make up
							   each part of the board where the property tokens
							   are placed. Although designated as integers, 
							   %c is used to display the letter tokens.
*/
void updateBoard(int propertyA, int propertyB, int propertyC, int propertyD, 
int propertyE, int propertyF, int propertyG, int propertyH, int propertyI,
int propertyJ, int propertyK, int propertyL, int propertyM, int propertyN, 
int propertyO, int tile0, int tile1, int tile2, int tile3, int tile4, int tile5,
int tile6, int tile7, int tile8, int tile9, int tile10, int tile11,
int tile12, int tile13, int tile14, int tile15, int tile16, int tile17,
int tile18, int tile19)
{
	//Local variable only used for loop statements in this function
	int x;
		
			system("cls");
			//Top letters
			printf("       e   f   g   h");
	
			printf("\n ");
			//First line of the board
			for(x = 1; x < 25; x+=4)
			{
				printf("+---");
			}
				printf("+\n ");
	
			//Second line of the board
			printf("|%c V|%c %c|%c %c|%c %c|%c %c|%c P|", 
			tile5, tile6, propertyE, tile7, propertyF, 
			tile8, propertyG, tile9, propertyH, tile10);
			
			//Third line of the board
			printf("\n ");
			for(x = 1; x < 25; x+=4)
			{
				printf("+---");
			}
				printf("+\n");
	
			//Fourth line of the board
			printf("d|%c %c|\t\t     |%c %c|i",
			tile4, propertyD, tile11, propertyI);
	
	
			//Fifth line of the board
			printf("\n ");
			x = 1;
			do
			{
				printf("+---+\t\t     ");
				x+=1;
			}	while (x <= 2);
	
			//Sixth line of the board
			printf("\n");
			printf("c|%c %c|\t\t     |%c %c|j",
			tile3, propertyC, tile12, propertyJ);
	
			//Seventh line of the board
			printf("\n ");
			x = 1;
			do
			{
				printf("+---+\t\t     ");
				x+=1;
			}	while (x <= 2);
	
			//Eighth line of the board
			printf("\n");
			printf("b|%c %c|\t\t     |%c %c|k",
			tile2, propertyB, tile13, propertyK);
	
			//Ninth line of the board
			printf("\n ");
			x = 1;
			do
			{
				printf("+---+\t\t     ");
				x+=1;
			}	while (x <= 2);
	
			//Tenth line of the board
			printf("\n");
			printf("a|%c %c|\t\t     |%c %c|l",
			tile1, propertyA, tile14, propertyL);
	
			//Eleventh line of the board
			printf("\n ");
			for(x = 1; x < 25; x+=4)
			{
				printf("+---");
			}
				printf("+\n ");
	
			//Twelfth line of the board
			printf("|%c G|%c %c", tile0, tile19, propertyO);
			printf("|%c T|%c %c", tile18, tile17, propertyN);
			printf("|%c %c|%c J|   ", tile16, propertyM, tile15);
	
	
			//Thirteenth line of the board
			printf("\n ");
			for(x = 1; x < 25; x+=4)
			{
				printf("+---");
			}
				printf("+\n");
	
			//Bottom letters
			printf("       o       n   m\n");
}


/*
void displayBalance() is a function that is used to display each player's balance.
Pre-condition: None
@param balance1 & balance2 = These are the values to be displayed in this function.
*/

void displayBalance(float balance1, float balance2)
{
	//Displays the players' balance
	printf("Account Balance:\n");
	printf("Player 1: %8.2f\n", balance1);
	printf("Player 2: %8.2f", balance2);
}

/*
void displayRound() is a function that displays what happened in the player's
					round. This includes displaying the output of rollDice() 
					(whether in play or debug mode), which property they landed 
					on, if they bought a property, or if they landed in 
					another player's property.
Pre-condition: None
@param maxdice = This is either dice1 or dice2 hence maxdice as it wouldn't be
				 appealing to see updates on where the player is at each 
				 iteration of checkDice() and updateBoard().
@param player1 = This is simply used to determine which player's turn.
@param dice = This is taken from rollDice() and used to display the integer 
			  returned.
@param yesOrNo = This is used to determine the actions of a player during their
				 round, whether they paid rent or bought a property or not.
@param *jail1 & *jail2 = Jail count is given here as well.
*/
void displayRound(int dice, int player1, int maxdice, int yesOrNo, 
int *jail1, int *jail2)
{
	char y = 121, Y = 89;
	
	maxdice = maxdice % 20;
	
	printf("\n\n");
	
	//Used to determine which player's turn
	if (player1 == 1)
		printf("Player 1 turn:\n");
	else if (player1 == 0)
		printf("Player 2 turn:\n");
	
	printf("- rolled a %d\n", dice);
	
	//Used to display where the player lands
	switch (maxdice)
	{
		case 0:
			break;
		case 1:
			printf("- landed on Property a\n");
			break;
		case 2:
			printf("- landed on Property b\n");
			break;
		case 3:
			printf("- landed on Property c\n");
			break;
		case 4:
			printf("- landed on Property d\n");
			break;
		case 5:
			printf("- landed on Just Visiting (V)");
			break;
		case 6:
			printf("- landed on Property e\n");
			break;
		case 7:
			printf("- landed on Property f\n");
			break;
		case 8:
			printf("- landed on Property g\n");
			break;
		case 9:
			printf("- landed on Property h\n");
			break;
		case 10:
			printf("- landed on Free Parking(P) tile\n");
			printf("- take a moment to chill here");
			break;
		case 11:
			printf("- landed on Property i\n");
			break;
		case 12:
			printf("- landed on Property j\n");
			break;
		case 13:
			printf("- landed on Property k\n");
			break;
		case 14:
			printf("- landed on Property l\n");
			break;
		case 15:
			printf("- landed on Go To Jail (J) tile\n");
			printf("- transferred to Just Visiting (V)\n");
			printf("  tile and shall skip two (2) turns");
			if (player1 == 1)
			{
			*jail1 = 3;
			}
			else if (player1 == 0)
			{
			*jail2 = 3;
			}
			break; 
		case 16:
			printf("- landed on Property m\n");
			break;
		case 17:
			printf("- landed on Property n\n");
			break;
		case 18:
			printf("- landed on Luxury Tax (T) tile\n");
			printf("- pay the banker 1,000,000.00");
			break;
		case 19:
			printf("- landed on Property o\n");
			break;
	}
	
	//Statement if ever the player wants to buy a property but doesn't have
	//enough funds
	if (yesOrNo == 0)
	{
		printf("- Not enough funds to purchase property\n");
	}
	
	//Conditional statements for displaying how much a player pays the other
	else if (yesOrNo == 1)
	{
		printf("- paid");
			if (player1 == 1)
			{
			printf(" player 2");
			}
			else if (player1 == 0)
			{
			printf(" player 1");
			}
				if (maxdice <= 4 && maxdice >= 1)
				printf(" -> 300000.00");
				else if (maxdice <= 9 && maxdice >= 6)
				printf(" -> 500000.00");
				else if (maxdice <= 14 && maxdice >= 11)
				printf(" -> 1000000.00");
				else if (maxdice == 19 || maxdice == 17 || maxdice == 16)
				printf(" -> 2000000.00");
	}
	
	//Conditional statements used for displaying if the player buys a property
	else if (yesOrNo == y || yesOrNo == Y)
	{
		printf("- bought");
		
		switch (maxdice)
	{
		case 0:
			break;
		case 1:
			printf(" property a");
			break;
		case 2:
			printf(" property b");
			break;
		case 3:
			printf(" property c");
			break;
		case 4:
			printf(" property d");
			break;
		case 5:
			break;
		case 6:
			printf(" property e");
			break;
		case 7:
			printf(" property f");
			break;
		case 8:
			printf(" property g");
			break;
		case 9:
			printf(" property h");
			break;
		case 10:
			break;
		case 11:
			printf(" property i");
			break;
		case 12:
			printf(" property j");
			break;
		case 13:
			printf(" property k");
			break;
		case 14:
			printf(" property l");
			break;
		case 15:
			break;
		case 16:
			printf(" property m");
			break;
		case 17:
			printf(" property n");
			break;
		case 18:
			break;
		case 19:
			printf(" property o");
			break;
	}
	}
}

/*
void changeValues() is the function used to have dynamic property values and
					rent fees.
Pre-condition: None
@param dice = This is either dice1 or dice2 to determine where in the board the
			  player is.
@param *propertyValue = This is the variable used to determine a property's value.
@param *rentFee = This is the variable used to determine the rent fee.
*/
void changeValues(int dice, int *propertyValue, int *rentFee)
{
	dice = dice % 20;
	//Conditional statement for different properties. 
	if (dice > 0 && dice <= 5)
	{
		*propertyValue = 2000000;
		*rentFee = 300000;
	}
	else if (dice > 5 && dice <= 10)
	{
		*propertyValue = 4000000;
		*rentFee = 500000;
	} 
	else if (dice > 10 && dice <= 15)
	{
		*propertyValue = 6000000;
		*rentFee = 1000000;
	}
	else if (dice >= 16 && dice <= 20)
	{
		*propertyValue = 8000000;
		*rentFee = 2000000;
	}
}
	
/*
int isThereOwner() is a function used to check if the property has an 'owner'.
				   In other words, it is used to check if the property holds a
				   value equal to 'X' or 'Y', the property tokens. 
Pre-condition: None
@param property = This is simply the property that is going to be checked.
*/
int isThereOwner(int property)
{
	return property == 'X' || property == 'Y';
}

/*
void payRent() is a function used to add and subtract a set amount from a player's
			   balance if they were to end up in another player's property.
Pre-condition: The player has to land on a tile where it is owner by another
			   player. This wouldn't persist if a player in their own property.
@param balance1 & balance2 = This is updated here as each player's balance
							 will be changed.
@param rentFee = This is a set value that is added and subtracted.
@param player1 = This is used to determine the which player's turn.
@param property = Used to check if the property is owner the player.
@param *yesOrNo = This is used to change yesOrNo to 1 to display paying rent.
*/
void payRent(float *balance1, float *balance2, int rentFee, int player1, 
int property, int *yesOrNo)
{
	if (player1 == 1 && property == 89)
		{
		*balance1 -= rentFee;
		*balance2 += rentFee;
		*yesOrNo = 1;
		}
	else if (player1 == 0 && property == 88)
		{
		*balance2 -= rentFee;
		*balance1 += rentFee;
		*yesOrNo = 1;
		}
}

/*
int buyProperty() is the function used for the player to buy a property.
Pre-condition: The property is not owner by either player.
@param *property = This is used to change the value of a property.
@param *balance1 & *balance2 = This is updated here as the players' balance will
							   be changed.
@param propertyValue = This is the set value subtracted from the player's balance.
@param player1 = This is used to determine which player's turn.
@returns the value of yesOrNo.
*/
int buyProperty(int *property, float *balance1, float *balance2,
int propertyValue, int player1)
{	
	char yesOrNo = 2;
	
			printf("\nDo you want to buy this property for %d (y/n)?\n", propertyValue);
			scanf(" %c", &yesOrNo);
			if ((yesOrNo == 121 || yesOrNo == 89) && player1)
				{
					if (*balance1 - propertyValue > 0)
					{
					*balance1 -= propertyValue;
					*property = 88;
					}
					else
					yesOrNo = 0;
				}
			else if ((yesOrNo == 121 || yesOrNo == 89) && player1 == 0)
				{
					if (*balance2 - propertyValue > 0)
					{
					*balance2 -= propertyValue;
					*property = 89;
					}
					else
					yesOrNo = 0;
				}
				
	return yesOrNo;
}

/*
void jailCount() is a function used to reduce *jail by one (1).
Pre-condition: Needs *jail to be greater than 0.
@param *jail = This is used here as it is decremented.
*/
void jailCount(int *jail)
{
	if (*jail > 0)
	{
		*jail = *jail - 1;
	}
}

/*
void collectGo() is a function used for a player to receive the 'Go' even if they
				 pass it.
@param storedice = This is used as it needs to confirm that the player passes go. 
@param *balance = This is needed as the balance will be changed.
@param *goCount = A variable specifically used for this function so the amount
				  is only collected once.
@param maxdice = This is to further ensure that the amount will only be collected once.
*/
void collectGo(int storedice, float *balance, int *goCount, int maxdice)
{
	/*Conditional statement to disallow collection of go in the start of the game
	as tile0 is where it is located.
	*/
	if (storedice >= 20 && (storedice % 20 == 0) && *goCount == 0)
	{
		*balance += 1000000;
		*goCount = 1;
	}
	else if (*goCount == 1 && maxdice > 20)
	{
		*goCount = 0;
	}
}

/*
void endGame() is a function used to display the end of a game.
Pre-condition: A player's balance is either 0 or less than zero.
@param balance = Either balance1 or balance2 is checked if it is less than or
				 equal to zero.
@param player1 = This is used to determine which player's turn.
@param *mode = This is used to change the mode.
*/
void endGame(int balance, int player1, int *mode)
{
	if (balance <= 0)
	{
		if (player1 == 1)
		{
			printf("\n- player 2 has won the game\n");
			Sleep(2000);
			*mode = 0;
		}
		else if (player1 == 0)
		{
			printf("\n- player 1 has won the game\n");
			Sleep(2000);		
			*mode = 0;
		}
	}
}
