#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include "Well.h"


enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

class Piece
{
public:
	Piece();
	virtual char pDisplay(int x, int y, int orient) const = 0;	// purely abstract, can't display abstract piece
	bool PieceInWell(Well& well) const;							// drops piece into the tetris board
	void nextPieceDisplay(Screen& scr) const;					// display status piece
	bool rotate(Well& well);									// changes orientation of piece
	bool pieceFall(Well& well);									// moves the piece down 
	virtual bool moveLeft(Well& well);							// moves piece to left
	virtual bool moveRight(Well& well);							// moves piece to right
	virtual void placePiece(Well& well) const;					// bricks the piece
	// last 3 virtual purely for the special pieces
protected:
	int m_x;
	int m_y;
	int m_orient;
private:
};

//////////////////////////////
//		PIECE CLASSES		//
//////////////////////////////

class T_Piece : public Piece
{
public:
	T_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
private:
	// 4 distinct orientations
	char orient_0[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ '#', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_1[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_2[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ '#', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_3[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ '#', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
};


class L_Piece : public Piece
{
public:
	L_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
private:
	// 4 distinct orientations
	char orient_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ '#', '#', '#', ' ' },
	{ '#', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_1[4][4] = {
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_2[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ '#', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_3[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', '#', ' ' } };
};


class J_Piece : public Piece
{
public:
	J_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
private:
	// 4 distinct orientations
	char orient_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', '#', '#' },
	{ ' ', ' ', ' ', '#' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_1[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', '#', '#', ' ' } };
	char orient_2[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', '#', '#' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_3[4][4] = {
	{ ' ', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
};


class O_Piece : public Piece
{
public:
	O_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
private:
	// 1 distinct orientations
	char orient_0[4][4] = {
	{ '#', '#', ' ', ' ' },
	{ '#', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
};


class S_Piece : public Piece
{
public:
	S_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
private:
	// 2 distinct orientations
	char orient_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ '#', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_1[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', ' ', ' ' } };
};


class Z_Piece : public Piece
{
public:
	Z_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
private:
	// 2 distinct orientations
	char orient_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ '#', '#', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_1[4][4] = {
	{ ' ', ' ', '#', ' ' },
	{ ' ', '#', '#', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
};


class I_Piece : public Piece
{
public:
	I_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
private:
	// 2 distinct orientations
	char orient_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ '#', '#', '#', '#' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_1[4][4] = {
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' } };
};


class Vapor_Piece : public Piece
{
public:
	Vapor_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
	virtual void placePiece(Well& well) const;
private:
	// 1 distinct orientations
	char orient_0[4][4] = {
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
};


class Foam_Piece : public Piece
{
public:
	Foam_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
	virtual void placePiece(Well& well) const;
	void fillFoam(Well& well, int x, int y, int t) const;
private:
	// 1 distinct orientations
	char orient_0[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
};


class Crazy_Piece : public Piece
{
public:
	Crazy_Piece() {};
	virtual char pDisplay(int x, int y, int orient) const;
	virtual bool moveLeft(Well& well);		
	virtual bool moveRight(Well& well);				
private:
	// 4 distinct orientations
	char orient_0[4][4] = {
	{ '#', ' ', ' ', '#' },
	{ ' ', '#', '#', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' } };
	char orient_1[4][4] = {
	{ ' ', ' ', ' ', '#' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', '#', ' ' },
	{ ' ', ' ', ' ', '#' } };
	char orient_2[4][4] = {
	{ ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ' },
	{ ' ', '#', '#', ' ' },
	{ '#', ' ', ' ', '#' } };
	char orient_3[4][4] = {
	{ '#', ' ', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ ' ', '#', ' ', ' ' },
	{ '#', ' ', ' ', ' ' } };
};

#endif // PIECE_INCLUDED
