
#include <vector>

#include "Well.h"
#include "UserInterface.h"

//////////////////////////////////////
//		MAINTENANCE FUNCTIONS		//
//////////////////////////////////////

// This clears the well for the next level
void Well::emptyWell()
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 1; j < m_width + 1; j++)			// when i play tetris, i leave the right most column empty
		{												// my original function didnt have the +1, and I never noticed
			tetBoard[i][j] = ' ';						// that portion of the well wasn't actually being cleared
		}
	}
}

// updates the coordinate with the character
void Well::updateTet(int x, int y, char c)
{
	tetBoard[y][x] = c;
}

// views the current board
char Well::viewTet(int x, int y) const
{
	return tetBoard[y][x];
}

// this function determines how many floors should be removed
int Well::floors()
{
	int removed = 0;
	int y, x;	// coordinates
	std::vector<int> floors;
	for (y = 17; y >= 0; y--)	// starting from the lowest floor
	{
		for (x = 1; x < 11; x++)	// moving along each column at row y
		{
			if (viewTet(x, y) == ' ')	// if ' ' present, floor is not complete
			{
				break;
			}
		}
		if (x == 11)
		{
			removed++;			// floor is complete
			floors.push_back(y);	// stores the completed row location
		}
	}
	while (floors.size() > 0)	// the following updates the removed floors
	{
		int temp = floors.back();
		floors.pop_back();
		for (temp; temp > 0; temp--)
		{
			for (x = 1; x < 11; x++)
			{
				updateTet(x, temp, viewTet(x, temp - 1));
			}
		}
		for (x = 1; x < 11; x++)
		{
			updateTet(x, 0, ' ');
		}
	}
	return removed;
}

//////////////////////////////////
//		PRIMARY FUNCTIONS		//
//////////////////////////////////

Well::Well(int width, int height)
	: m_width(width), m_height(height)
{
	// generate the left wall
	for (int i = 0; i < height; i++)
	{
		tetBoard[i][0] = '@';
	}
	// generate the right wall
	for (int i = 0; i < height; i++)
	{
		tetBoard[i][11] = '@';
	}
	// generate the bottom wall
	for (int i = 0; i < width + 2; i++)
	{
		tetBoard[height][i] = '@';
	}
	// Fill the inside with empties
	for (int row = 0; row < height; row++)
	{
		for (int col = 1; col <= width; col++)
		{
			tetBoard[row][col] = ' ';		// test it by placing 'O' instead of ' '
		}
	}
}

Well::~Well()	// unnecessary? 
{}

void Well::display(Screen& screen, int x, int y)
{
	for (int row = y; row <= m_height; row++)	
	{
		for (int col = x; col <= m_width + 1; col++)		// goes through the bounds of the tetris game, displaying each character.
		{
			screen.gotoXY(col, row);
			screen.printChar(tetBoard[row][col]);
		}
	}
	screen.refresh();
}
