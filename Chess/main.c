#include "graphTe.h"

const unsigned short int pieceSize = 100;

char pieces[8][8];	

unsigned int mouseState = 0, selectedX, selectedY, newX, newY;
POINT mPos;

void resetBoard()
{
	char newPieces[8][8] = {{'r', 'p',  0 ,  0 ,  0 ,  0 , 'P', 'R'},
					 		{'n', 'p',  0 ,  0 ,  0 ,  0 , 'P', 'N'},
					 		{'b', 'p',  0 ,  0 ,  0 ,  0 , 'P', 'B'},
					 		{'q', 'p',  0 ,  0 ,  0 ,  0 , 'P', 'Q'},
					 		{'k', 'p',  0 ,  0 ,  0 ,  0 , 'P', 'K'},
					 		{'b', 'p',  0 ,  0 ,  0 ,  0 , 'P', 'B'},
					 		{'n', 'p',  0 ,  0 ,  0 ,  0 , 'P', 'N'},
					 		{'r', 'p',  0 ,  0 ,  0 ,  0 , 'P', 'R'}};	

	memcpy(pieces, newPieces, 64 * sizeof(char));
}

void drawPiece(int x, int y, int posX, int posY)
{
	switch(pieces[x][y])
	{
		case 'r':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/blackRook.bmp",rgb(0, 255, 0));
			break;
		case 'n':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/blackKnight.bmp",rgb(0, 255, 0));
			break;
		case 'b':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/blackBishop.bmp",rgb(0, 255, 0));
			break;
		case 'q':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/blackQueen.bmp",rgb(0, 255, 0));
			break;
		case 'k':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/blackKing.bmp",rgb(0, 255, 0));
			break;
		case 'p':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/blackPawn.bmp",rgb(0, 255, 0));
			break;

		case 'R':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/whiteRook.bmp",rgb(0, 255, 0));
			break;
		case 'N':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/whiteKnight.bmp",rgb(0, 255, 0));
			break;
		case 'B':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/whiteBishop.bmp",rgb(0, 255, 0));
			break;
		case 'Q':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/whiteQueen.bmp",rgb(0, 255, 0));
			break;
		case 'K':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/whiteKing.bmp",rgb(0, 255, 0));
			break;
		case 'P':
			transparentImage(posX, posY, pieceSize, pieceSize, "pieces/whitePawn.bmp",rgb(0, 255, 0));
			break;
	}
}

void changeMouseState()
{
	if(mouseState)
		mouseState = 0;
	else
		mouseState = 1;
}

void movePiece()
{
	mPos = getMousePosition();

	if(checkKeyLiveInput(VK_LBUTTON))
	{
		if(!mouseState)
		{
			selectedX = mPos.x / pieceSize;
			selectedY = mPos.y / pieceSize;

			if(pieces[selectedX][selectedY] && selectedX >= 0 && selectedX < 8 && selectedY >= 0 && selectedY < 8)
			{
				changeMouseState();
			}
		}
	}
	else
	{
		if(mouseState)
		{
			newX = mPos.x / pieceSize;
			newY = mPos.y / pieceSize;

			if(newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
			{
				char temp = pieces[selectedX][selectedY];
				pieces[selectedX][selectedY] = 0;
				pieces[mPos.x / pieceSize][mPos.y / pieceSize] = temp;

				changeMouseState();
			}
			else
			{
				changeMouseState();
			}
		}
	}

	if(checkKeyLiveInput(VK_END) && !mouseState)
	{
		resetBoard();
	}
}

void render()
{
	//clearScreen
	fill(rgb(0, 0, 0));

	//board:
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			if((x + y) % 2)
				rect(x * pieceSize, y * pieceSize, pieceSize, pieceSize, rgb(184, 136, 97));
			else
				rect(x * pieceSize, y * pieceSize, pieceSize, pieceSize, rgb(239, 220, 180));

			drawPiece(x, y, x * pieceSize, y * pieceSize);
		}
	}

	//MousePiece:
	if(mouseState == 1)
	{
		if((selectedX + selectedY) % 2)
			rect(selectedX * pieceSize, selectedY * pieceSize, pieceSize, pieceSize, rgb(184, 136, 97));
		else
			rect(selectedX * pieceSize, selectedY * pieceSize, pieceSize, pieceSize, rgb(239, 220, 180));

		drawPiece(selectedX, selectedY, mPos.x - pieceSize / 2, mPos.y - pieceSize / 2);
	}

	display();
}

int main()
{
	initHost();
	setWindowTitle("Chess - Ene Alexandru_Florin");
	setWindowSize(1000, 1000);
	update();


	resetBoard();
	while(1)
	{		
		movePiece();
		render();
	}

	releaseHost();
}