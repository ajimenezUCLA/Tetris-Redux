#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"

#include <string>

class Game
{
  public:
    Game(int width, int height);
	~Game();	// TODO: DELETE POINTERS
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
	void getRandPiece(Piece* &p);		// Piece* getRandPiece( & ) alternative? test effectiveness
										// got really stuck on this part
	//Piece* getRandoPiece( ... this didn't work in the last 3 attempts
	// TODO: rework this

  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
	int		m_score;
	int		m_rows_left;

	Piece* m_curr_Piece;
	Piece* m_next_Piece;
};

#endif // GAME_INCLUDED
