#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

//////////////////////////
//		CONSTANTS		//
//////////////////////////

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

//////////////////////////////////
//		HELPER FUNCTIONS		//
//////////////////////////////////

// ensures end of status values are in the same location
std::string intString(int n)
{
	if (n < 0)
	{
		n = 0;	// no negative scores
	}
	std::stringstream s_string;
	s_string << n;	// ostream insertion
	std::string string = s_string.str();
	while (string.size() < 7)
	{
		string = " " + string;
	}
	return string;

	// TODO: REPAIR THE BOTTOM FUNCTION
}

void Game::getRandPiece(Piece* &p)	// this was tricky, dereferencing a pointer instead of Piece * doSomething(& )
{
	//	PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
	//	PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES

	switch (chooseRandomPieceType())
	{
	case PIECE_I:
			p = new	I_Piece;	break;
	case PIECE_L:
			p = new	L_Piece;	break;
	case PIECE_J:
			p = new	J_Piece;	break;
	case PIECE_T:
			p = new	T_Piece;	break;
	case PIECE_O:
			p = new	O_Piece;	break;
	case PIECE_S:
			p = new	S_Piece;	break;
	case PIECE_Z:
			p = new	Z_Piece;	break;
	case PIECE_VAPOR:
			p = new	Vapor_Piece;break;
	case PIECE_FOAM:
			p = new	Foam_Piece;	break;
	case PIECE_CRAZY:
			p = new	Crazy_Piece;break;
	}
}

//////////////////////////////
//		CONSTRUCTORS		//
//////////////////////////////

Game::Game(int width, int height)
	: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_rows_left(5), m_score(0), m_well(width, height)
{
	m_next_Piece = nullptr;
	m_curr_Piece = nullptr;	// was running out of room in init list
}

Game::~Game()
{
	delete m_next_Piece;
	delete m_curr_Piece;
}

//////////////////////////////////
//		PRIMARY FUNCTIONS		//
//////////////////////////////////

// Old play function
/*
void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}
*/

void Game::play()
{
	m_well.display(m_screen, WELL_X, WELL_Y);
	displayStatus();  //  score, rows left, level
	displayPrompt("Press the Enter key to begin playing Chetyris!");
	waitForEnter();  // [in UserInterface.h]

	double timeMax = std::max(1000 - (100 * (m_level - 1)), 100);	// time keeping purposes
	Timer timeStart;												// good place for time keeping?

	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);		// must be implemented here, not displaystatus
	m_screen.printString("Next piece:");							// reason: it appears only when you start the game

	getRandPiece(m_curr_Piece);										// get a piece and dorp it into the well

	for (;;)
	{

		getRandPiece(m_next_Piece);						// load and display the next piece
		m_next_Piece->nextPieceDisplay(m_screen);

		if (!m_curr_Piece->PieceInWell(m_well))			// stops the game if you reach the top of the well
		{
			m_well.display(m_screen, WELL_X, WELL_Y); break;
		}

		for (;;)
		{
			m_well.display(m_screen, WELL_X, WELL_Y);
			double timeEnd = timeStart.elapsed() + timeMax;		//not sure if this is best place for it
			while (timeStart.elapsed() < timeEnd)
			{
				char input;
				if (getCharIfAny(input))
				{
					switch (input)
					{
					case ' ':			// press space to drop the piece instantly
						for (;;)
						{
							if (!m_curr_Piece->pieceFall(m_well))
							{
								timeEnd = 0;
								break;
							}
						}
						break;
					case ARROW_UP:		// rotate
						if (m_curr_Piece->rotate(m_well))
						{
							m_well.display(m_screen, WELL_X, WELL_Y);
							//m_screen.refresh();
						}
						break;
					case ARROW_DOWN:	// make piece fall quickly
						if (m_curr_Piece->pieceFall(m_well))
						{
							timeEnd = timeStart.elapsed() + timeMax;
							m_well.display(m_screen, WELL_X, WELL_Y);
							//m_screen.refresh();
						}
						break;
					case ARROW_LEFT:	// move piece to the left
						if (m_curr_Piece->moveLeft(m_well))
						{
							m_well.display(m_screen, WELL_X, WELL_Y);
							//m_screen.refresh();
						}
						break;
					case ARROW_RIGHT:	// move piece to the right			// NOTE* according to spec '4' and left arrow key
						if (m_curr_Piece->moveRight(m_well))				// are already combined for same input, (from windows interface)
						{
							m_well.display(m_screen, WELL_X, WELL_Y);
							//m_screen.refresh();
						}
						break;
					case 'Q':												// forgot return, took a while to figure out
					case 'q':
						displayPrompt("Game Over!  Press the Enter key to exit!");
						waitForEnter();
						return;
					default:
						;
					}
					m_screen.refresh();
				}
			}
			discardPendingKeys();
			//	end modify this segment	//
			if (!m_curr_Piece->pieceFall(m_well))
			{
				m_curr_Piece->placePiece(m_well);
				switch (m_well.floors())
				{
				case 1:
					m_score = 100 + m_score;
					m_rows_left = m_rows_left - 1;
					break;
				case 2:
					m_score = 200 + m_score;
					m_rows_left = m_rows_left - 2;
					break;
				case 3:
					m_score = 400 + m_score;
					m_rows_left = m_rows_left - 3;
					break;
				case 4:
					m_score = 800 + m_score;
					m_rows_left = m_rows_left - 4;
					break;
				case 5:
					m_score = 1600 + m_score;
					m_rows_left = m_rows_left - 5;
					break;
				default:
					;
				}
				m_well.display(m_screen, WELL_X, WELL_Y);
				displayStatus();
				delete m_curr_Piece;
				m_curr_Piece = m_next_Piece;
				break;
			}
			m_screen.refresh();
		}
		if (!playOneLevel())
		{
			continue;
			//break;	//* NOTE break broke my function, incorrect nesting?
		}
		
		m_level++;
		m_rows_left = 5 * m_level;
		m_well.emptyWell();
		getRandPiece(m_next_Piece);
		displayPrompt("Good job!  Press the Enter key to start next level!");
		waitForEnter();
		displayStatus();
	}
	displayPrompt("Game Over!  Press the Enter key to exit!");
	waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

//////////////////////////////
//		PLAY FUNCTIONS		//
//////////////////////////////

/// better method? test this. ask about use of clearline function in OH
void Game::displayStatus()
{
	// display score
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printString("Score:     ");
	m_screen.printStringClearLine(intString(m_score));
	// display rows left
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printString("Rows left: ");
	m_screen.printStringClearLine(intString(m_rows_left));
	// display level
	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printString("Level:     ");
	m_screen.printStringClearLine(intString(m_level));

	m_screen.refresh();
}

// determines if we can play again
bool Game::playOneLevel()
{
	if (m_rows_left <= 0)
	{
		return true;
	}
	return false;
}