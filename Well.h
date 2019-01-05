#ifndef WELL_INCLUDED
#define WELL_INCLUDED

class Screen;

class Well
{
public:
	Well(int width, int height);
	~Well();
	void display(Screen& screen, int x, int y);
	void emptyWell();	// new well, for a new game
	void updateTet(int x, int y, char c);	// updates the tetris pixel
	char viewTet(int x, int y) const;		// view tetris piece
	int floors();	// tells you how many floors filled
private:
	int m_width;
	int m_height;
	int tetBoard[19][12];	// the tetris section is 19 rows by 12 columns
};

#endif // WELL_INCLUDED
