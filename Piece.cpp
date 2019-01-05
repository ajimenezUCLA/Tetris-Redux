#include "Piece.h"
#include "Game.h"

#include <cstdlib>
#include <algorithm>
#include <cmath>

//////////////////////////////////
//		PIECE - SUPERCLASS		//
//////////////////////////////////

Piece::Piece()
	: m_x(3), m_y(0), m_orient(0)
{
	// "upper-left corner of the bounding box will be placed at X=3, Y=0"
	// setting orientation to zero by default, as per the spec
}

bool Piece::PieceInWell(Well& well) const
{
	bool temp = true;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (pDisplay(i, j, 0) == '#')
			{
				if (well.viewTet(j + 4, i) != ' ')
				{
					temp = false;
				}
				well.updateTet(j + 4, i, '#');
			}
		}
	}
	return temp;
}

//const int NEXT_PIECE_X = 16;	// i learned about the extern function... not sure if allowed to use it
//const int NEXT_PIECE_Y = 4;
void Piece::nextPieceDisplay(Screen& scr) const	// this function is to display the next piece
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			scr.gotoXY(j + 16, i + 4);
			scr.printChar(pDisplay(i, j, 0));
		}
	}
	scr.refresh();
}

bool Piece::rotate(Well& well)
{
	int temp_orient = m_orient;
	if (temp_orient < 3)
	{
		temp_orient++;
	}
	else
	{
		temp_orient = 0;
	}
	for (int temp1 = 0; temp1 < 4; temp1++)
	{
		for (int temp2 = 0; temp2 < 4; temp2++)
		{
			if (pDisplay(temp1, temp2, temp_orient) == '#' && well.viewTet(m_x + temp2 + 1, m_y + temp1) != ' ' && well.viewTet(m_x + temp2 + 1, m_y + temp1) != '#')
			{
				return false;
			}
		}
	}
	for (int temp1 = 0; temp1 < 4; temp1++)
	{
		for (int temp2 = 0; temp2 < 4; temp2++)
		{
			if (well.viewTet(m_x + temp2 + 1, m_y + temp1) == '#')
			{
				well.updateTet(m_x + temp2 + 1, m_y + temp1, ' ');
			}
			if (pDisplay(temp1, temp2, temp_orient) == '#')
			{
				well.updateTet(m_x + temp2 + 1, m_y + temp1, pDisplay(temp1, temp2, temp_orient));
			}
		}
	}
	m_orient = temp_orient;
	return true;
}

bool Piece::pieceFall(Well& well)		// similar to moveLeft and moveRight
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (well.viewTet(m_x + j + 1, m_y + i) == '#')
			{
				if (m_y + i + 1 >= 18 || well.viewTet(m_x + j + 1, m_y + i + 1) == '$' || well.viewTet(m_x + j + 1, m_y + i + 1) == '*')
				{
					return false;		// makes sure in bounds and not obstructing
				}
			}
		}
	}
	// now it is cleared for changes
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (well.viewTet(m_x + j + 1, m_y + i) == '#')
			{
				well.updateTet(m_x + j + 1, m_y + i, ' ');
				well.updateTet(m_x + j + 1, m_y + i + 1, '#');
			}
		}
	}
	m_y++;
	return true;
}

bool Piece::moveLeft(Well& well)		// code is essnetially the same as the moveRight, 
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_x + i + 1 < 0)
			{
				continue;
			}
			if (well.viewTet(m_x + i + 1, m_y + j) == '#')
			{
				if (well.viewTet(m_x + i, m_y + j) == '$' || well.viewTet(m_x + i, m_y + j) == '*' || m_x + i <= 0)
				{
					return false;
				}
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (well.viewTet(m_x + i + 1, m_y + j) == '#')
			{
				well.updateTet(m_x + i + 1, m_y + j, ' ');
				well.updateTet(m_x + i, m_y + j, '#');
			}
		}
	}
	m_x--;
	return true;
}

bool Piece::moveRight(Well& well)
{
	for (int i = 3; i >= 0; i--)			// this portion ensures we're within defined behavior
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_x + i + 1 >= 12)
			{
				continue;
			}
			if (well.viewTet(m_x + i + 1, m_y + j) == '#')	// it has to be this complicated, other methods break the game horribly.
			{
				if (well.viewTet(m_x + i+ 2, m_y + j) == '$' || well.viewTet(m_x + i+2, m_y + j) == '*' || m_x + i + 2 >= 11)
				{
					return false;
				}
			}
		}
	}
	for (int i = 3; i >= 0; i--)							// boundaries met, replace piece.
	{
		for (int j = 0; j < 4; j++)
		{
			if (well.viewTet(m_x + i + 1, m_y + j) == '#')
			{
				well.updateTet(m_x + i + 2, m_y + j, '#');	// move piece to right
				well.updateTet(m_x + i + 1, m_y + j, ' ');	// remove old position
			}
		}
	}
	m_x++;
	return true;
}

// NOTE* : wasn't working 2 builds ago, not sure why. really simple
// TODO: test functions calling this

void Piece::placePiece(Well& well) const
{
	for (int i = m_y; i < m_y + 4; i++)		// for (i, j; j< m_x ; i++, j++) 
	{
		for (int j = m_x + 1; j < m_x + 5; j++)
		{
			if (well.viewTet(j, i) == '#')		
			{
				well.updateTet(j, i, '$');		// replaces the '#' with '$'
			}
		}
	}
}

//////////////////////////////////
//		PIECES - SUBCLASS		//
//////////////////////////////////

// *NOTE 1: Utilizing switch case fall through
// *NOTE 2: to remove the "not all control paths return a value"
//			I have to include an exit(1), meaning failure (undefined behavior)

// The T Piece (4 distinct)
char T_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
		return orient_0[x][y];
	case 1:
		return orient_1[x][y];
	case 2:
		return orient_2[x][y];
	case 3:
		return orient_3[x][y];
	}
	exit(1);
}

// The L Piece (4 distinct)
char L_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
		return orient_0[x][y];
	case 1:
		return orient_1[x][y];
	case 2:
		return orient_2[x][y];
	case 3:
		return orient_3[x][y];
	}
	exit(1);
}

// The J Piece (4 distinct)
char J_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
		return orient_0[x][y];
	case 1:
		return orient_1[x][y];
	case 2:
		return orient_2[x][y];
	case 3:
		return orient_3[x][y];
	}
	exit(1);
}

// The O Piece (1 distinct)
char O_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return orient_0[x][y];
	}
	exit(1);
}

// The S Piece ( 2 distinct - 0 & 2, 1 & 3 )
char S_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
	case 2:
		return orient_0[x][y];
	case 1:
	case 3:
		return orient_1[x][y];
	}
	exit(1);
}

// The Z Piece ( 2 distinct - 0 & 2, 1 & 3 )
char Z_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
	case 2:
		return orient_0[x][y];
	case 1:
	case 3:
		return orient_1[x][y];
	}
	exit(1);
}

// The I Piece ( 2 distinct - 0 & 2, 1 & 3)
char I_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
	case 2:
		return orient_0[x][y];
	case 1:
	case 3:
		return orient_1[x][y];
	}
	exit(1);
}

// The Vapor Piece ( 1 distinct )
char Vapor_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return orient_0[x][y];
	}
	exit(1);
}

void Vapor_Piece::placePiece(Well& well) const
{
	for (int i = m_x + 2; i < m_x + 4; i++)
	{
		for (int j = std::max(m_y - 2, 0); j <= std::min(m_y + 2, 17); j++)
		{
			well.updateTet(i, j, ' ');
		}
	}
}

// The Foam Piece ( 1 distinct )
char Foam_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return orient_0[x][y];
	}
	exit(1);
}

void Foam_Piece::fillFoam(Well& well, int x, int y, int t) const
{
	if (t <= 0)
	{
		return;
	}
	if (well.viewTet(x, y) != ' ')
	{
		return;
	}
	else
	{
		well.updateTet(x, y, '*');
		fillFoam(well, x + 1, y, t-1);
		fillFoam(well, x - 1, y, t-1);
		fillFoam(well, x, y + 1, t-1 );
		fillFoam(well, x, y - 1, t-1);
	}
}
// TODO:
// https://www.geeksforgeeks.org/flood-fill-algorithm-implement-fill-paint/
// good? need to look into it


void Foam_Piece::placePiece(Well& well) const
{
	fillFoam(well, m_x+2, m_y, 3);
}

// The Crazy Piece ( 4 distinct)
char Crazy_Piece::pDisplay(int x, int y, int orient) const
{
	switch (orient)
	{
	case 0:
		return orient_0[x][y];
	case 1:
		return orient_1[x][y];
	case 2:
		return orient_2[x][y];
	case 3:
		return orient_3[x][y];
	}
	exit(1);
}

bool Crazy_Piece::moveLeft(Well& well)
{
	return Piece::moveRight(well);
}
bool Crazy_Piece::moveRight(Well& well)
{
	return Piece::moveLeft(well);
}
