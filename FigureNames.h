#pragma once
#include <SFML/Graphics.hpp>
#define ROWS 8
#define COLUMS 8
#define Board_Cells 64
using namespace sf;

extern char ChessBoard[Board_Cells];

extern class figure Board;

extern class figure B_Knight;
extern class figure B_Pawn;
extern class figure B_Rook;
extern class figure B_King;
extern class figure B_Queen;
extern class figure B_Bishop;

extern class figure W_Knight;
extern class figure W_Pawn;
extern class figure W_Rook;
extern class figure W_King;
extern class figure W_Queen;
extern class figure W_Bishop;

// AI THINGS
extern bool AI_turn_flag;

