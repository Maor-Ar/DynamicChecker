
/* =========================================================
 * Student name:
 *   Authers: Maor Arnon (ID: 205974553) and Vlad Kelar (ID:320467335)
 *   emails: maorar1@ac.sce.ac.il    angerag3@Gmail.com
 *   Department of Computer Engineering
 *
 * Course:
 *     C Programming (ipc084) / David Tankos
 *     Final Assignment 
 *
 * Date: 04-June-2020 21:24
 * Last submitting date: 05-June-2020 12:00
 * ========================================================= */


#define _CRT_SECURE_NO_WARNINGS
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define PINK "\033[1;35m"
#define MAGENTA "\033[1;36m"
#define WHITE "\033[0m"    
//strings to change text colors
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct
{
	char name[20];
	char color[20];
}player; 

typedef enum
{
	FALSE,
	TRUE
}bool;

typedef struct
{
	char color[20];
	bool exist;
}piece;

//piece** set_board(int size, player player1, player player2);
//void print_board(piece** board, int size);
//void game_on();
//bool players_turn(piece** board, player player1, int x1, int y1, int x2, int y2, int size);
//bool checkwinner(piece** board, player player, int size);

piece** set_board(int size, player player1, player player2);
void print_board(piece** board, int size);
void menu();
void game_on();
bool players_turn(piece** board, player player1, int x1, int y1, int x2, int y2, int size);
void freeall(int,piece***);
bool checkwinner(piece** board, player player, int size);


void main()
{
	menu();
}

piece** set_board(int size, player player1 ,player player2)
{
	piece** board = NULL;
	board =(piece**) malloc(sizeof(piece*) * size);
	if (!board)
	{
		printf("Error, could not allocate memory.");
		return NULL;
	}
	for (int i = 0; i < size; i++)
	{
		board[i] = (piece*)malloc(sizeof(piece) * size);
		if (!board[i])
		{
			printf("Error, could not allocate memory.");
			return NULL;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((i + j) % 2 == 0) //every other space is empty
			{
				board[i][j].exist = FALSE;
			}
			else if (i > 2 && i < (size - 3))//all the middle lines are empty
			{
				board[i][j].exist = FALSE;
			}
			else if (i < 3)//if its on the upper side of the board
			{
				strcpy(board[i][j].color,player1.color);
			}
			else //lower side of the board
				strcpy(board[i][j].color,player2.color);
		}
	}
	return board;
}

void menu()
{
	int menu;

	printf("%sChoise the option you like to use:\n%s1)Start the game\n%s2)How to play?\n%s3)About\n%s4)Quit\n%s", RED, GREEN, YELLOW, PINK, MAGENTA, WHITE);
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		game_on();
		break;
	case 2:
		printf("%s1)%sThe two players alternate turns and can only move their own pieces. \n%s2)%sThe dark squares are the only ones that may be occupied on the board. The light squares must remain empty. \n%s3)%sEach turn involves the moving of one piece, which can consist of a piece moving forward to a diagonally adjacent square that is unoccupied,\nor jumping forward over an occupied diagonally adjacent square, provided that the square beyond is also empty. \n%s4)%sIf a player jumps over their opponent’s piece, they have successfully captured that piece and it is removed from the game. \n%s5)%sEach piece is initially referred to as a man, but if it reaches the furthest side of the board it becomes a king.\nWhen this happens, the player stacks an additional piece on top of the original to signify the change. \n%s6)%sMen may only move forward, but kings can move diagonally forwards as well as backwards. \n%s7)%sMultiple pieces maybe jumped by both men and kings provided that there are successive unoccupied squares beyond each piece that is jumped.%s", WHITE, YELLOW, WHITE, YELLOW, WHITE, YELLOW, WHITE, YELLOW, WHITE, YELLOW, WHITE, YELLOW, WHITE, YELLOW, WHITE);
		break;
	case 3:
		printf("%sCheckers Game on C created by:\nVladislav Kelar, 320467335 and Maor Arnon, 205974553%s", PINK, WHITE);
		break;
	case 4:
		printf("%sYou choice to quit the game.%s", RED, WHITE);
		break;
	}
}

void print_board(piece** board, int size)
{
	printf("%s\n    ",WHITE);
	for (int j = 0; j < size; j++)
		printf("----");
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("%3d|",i+1);
		for (int j = 0; j < size; j++)
		{
			if (board[i][j].exist)
				printf("%s O \033[0m|", board[i][j].color);
			else
				printf("   |");
		}
		printf("\n");
		printf("    ");
		for (int j = 0; j < size; j++)
			printf("----");
		printf("\n");
	}
	printf("    ");
	for (int j = 0; j < size; j++)
		printf(" %c  ", ('a' + j));
	printf("\n");
}

void game_on()
{
	int menu, size = 0;
	player player1, player2;
	while (size < 8 || size>26)
	{
		printf("Enter the size of your board (between 8 and 26):\n");
		scanf("%d", &size);
	}
	printf("Your board size is %dX%d\nEnter first player name: ", size, size);
	scanf("%s", player1.name);
	printf("Choose first player color:\n%s1) Red. %s\n2) Green. %s\n3) Yellow. %s\n4)Pink %s\n5) Magenta. %s\n",RED,GREEN,YELLOW,PINK,MAGENTA,WHITE);
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		strcpy(player1.color, RED);
		break;
	case 2:
		strcpy(player1.color, GREEN);
		break;
	case 3:
		strcpy(player1.color, YELLOW);
		break;
	case 4:
		strcpy(player1.color, PINK);
		break;
	case 5:
		strcpy(player1.color, MAGENTA);
		break;
	}

	printf("Enter second player name: ");
	scanf("%s", player2.name);
	printf("Choose second player color:\n%s1) Red. %s\n2) Green. %s\n3) Yellow. %s\n4) Pink %s\n5) Magenta. %s\n", RED, GREEN, YELLOW, PINK, MAGENTA, WHITE);
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		strcpy(player2.color, RED);
		break;
	case 2:
		strcpy(player2.color, GREEN);
		break;
	case 3:
		strcpy(player2.color, YELLOW);
		break;
	case 4:
		strcpy(player2.color, PINK);
		break;
	case 5:
		strcpy(player2.color, MAGENTA);
		break;
	}
	while (!strcmp(player1.color,player2.color))
	{
		printf("player1 color is identical to player 2..choose another color\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1:
			strcpy(player2.color, RED);
			break;
		case 2:
			strcpy(player2.color, GREEN);
			break;
		case 3:
			strcpy(player2.color, YELLOW);
			break;
		case 4:
			strcpy(player2.color, PINK);
			break;
		case 5:
			strcpy(player2.color, MAGENTA);
			break;
		}
	}

	piece** board = set_board(size, player1, player2);
	int y1,y2;
	char x1,x2;


	for(;;)
	{
		print_board(board,size);
		while (1)
		{
			printf("%s%s%s\n",player1.color, player1.name,WHITE);
			printf("Choose a piece to move(number than letter):");
			scanf("%d%c", &y1, &x1);
			printf("Where to(number than letter):");
			scanf("%d%c", &y2, &x2);
			if (players_turn(board, player1, (int)x1 - 'a', y1-1, (int)x2 - 'a', y2-1, size))
				break;
		}
		if (checkwinner(board, player1, size))
		{
			printf("%sCongradulations %s you have won!!!%s",player1.color,player1.name,WHITE);
			break;
		}
		print_board(board, size);
		while (1)
		{
			printf("%s%s%s\n", player2.color, player2.name, WHITE);
			printf("Choose a piece to move(number than letter):");
			scanf("%d%c", &y1, &x1);
			printf("Where to(number than letter):");
			scanf("%d%c", &y2, &x2);
			if (players_turn(board, player2, (int)x1 - 'a', y1 - 1, (int)x2 - 'a', y2 - 1, size))
				break;
		}
		if (checkwinner(board, player2, size))
		{
			printf("%sCongradulations %s you have won!!!%s", player2.color, player2.name, WHITE);
			break;
		}
	}

	return;
}

bool players_turn(piece** board, player player1, int x1, int y1, int x2, int y2,int size)
{
	
	if (x2 > size || y2 > size || x2 < 0 || y2 < 0)
	{
		printf("Destenetion is out of bounds.\n");
		return FALSE;
	}
	if (x1 > size || y1 > size || x1 < 0 || y1 < 0)
	{
		printf("Chosen piece is out of bounds.\n");
		return FALSE;
	}
	if (strcmp(player1.color, board[y1][x1].color))
	{
		printf("This is not your piece.");
		return FALSE;
	}
	if (!board[y1][x1].exist)
	{
		printf("There is no piece there.");
		return FALSE;
	}
	if (board[y2][x2].exist)
	{
		printf("You cant land on another piece");
		return FALSE;
	}

	if ( ((x1 - x2) == 1 && (y1 - y2) == 1) || ( (x1 - x2) == -1 && (y1 - y2) == -1) || ( (x1 - x2) == 1 && (y1 - y2) == -1) || ( (x1 - x2) == -1) && (y1 - y2) == 1 )//if it moves to the near corners.
	{
		if (!board[y2][x2].exist)
		{

			board[y1][x1].exist = FALSE;
			board[y2][x2].exist = TRUE;
			strcpy(board[y2][x2].color, player1.color);
			return TRUE;
		}
		else
		{
			printf("You cant land on another piece");
			return FALSE;
		}
	}
	else if((((x1 - x2) == 2 && (y1 - y2) == 2))||(x2-x1)==2&& (y2 - y1) == 2|| (x1 - x2) == 2 && (y2 - y1) == 2|| (x2 - x1) == 2 && (y1 - y2) == 2)
		if (board[(y1 + y2) / 2][(x1 + x2) / 2].exist && strcmp(board[(y1 + y2) / 2][(x1 + x2) / 2].color,player1.color) )//check if exists a piece to eat and if its the enemy
		{
			board[y1][x1].exist = FALSE;
			board[y2][x2].exist = TRUE;
			board[(y1 + y2) / 2][(x1 + x2) / 2].exist = FALSE;
			strcpy(board[y2][x2].color, player1.color);
			return TRUE;
		}
		
		
		printf("You cant place it here.");
		return FALSE;


}

bool checkwinner(piece** board, player player,int size) //checks if the player have won the game.
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j].exist && player.color != board[i][j].color)
				return FALSE;
		}
	}
	return TRUE;
}