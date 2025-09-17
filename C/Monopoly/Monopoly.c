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

#include "Monopoly.h"

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
	

