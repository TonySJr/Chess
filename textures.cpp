#include "pch.h"
#include "FigureNames.h"
#include "figure.h"
#include "functions.h"
using namespace sf;
char ChessBoard[Board_Cells] =   {'t','l','s','f','k','s','l','t',
                                  'p','p','p','p','p','p','p','p',
                                  '0','0','0','0','0','0','0','0',
                                  '0','0','0','0','0','0','0','0',
                                  '0','0','0','0','0','0','0','0',
                                  '0','0','0','0','0','0','0','0',
                                  'P','P','P','P','P','P','P','P',
                                  'T','L','S','F','K','S','L','T'};
//

figure Board("Images/Board.png");
figure B_Rook(0, 0, "Images/B_Rook.png");
figure B_Knight(0, 0, "Images/B_Knight.png");
figure B_Bishop(0, 0, "Images/B_Bishop.png");
figure B_Queen(0, 0, "Images/B_Queen.png");
figure B_King(0, 0, "Images/B_King.png");
figure B_Pawn(0, 0, "Images/B_Pawn.png");

figure W_Rook(0, 0, "Images/W_Rook.png");
figure W_Knight(0, 0, "Images/W_Knight.png");
figure W_Bishop(0, 0, "Images/W_Bishop.png");
figure W_Queen(0, 0, "Images/W_Queen.png");
figure W_King(0, 0, "Images/W_King.png");
figure W_Pawn(0, 0, "Images/W_Pawn.png");

bool InitTextures()
{
    if (!Board.textureready())
        return false;

    if (!B_Rook.textureready())
        return false;

    if (!B_Knight.textureready())
        return false;

    if (!B_Bishop.textureready())
        return false;

    if (!B_Queen.textureready())
        return false;

    if (!B_King.textureready())
        return false;

    if (!B_Pawn.textureready())
        return false;

    if (!W_Rook.textureready())
        return false;

    if (!W_Knight.textureready())
        return false;

    if (!W_Bishop.textureready())
        return false;

    if (!W_Queen.textureready())
        return false;

    if (!W_King.textureready())
        return false;

    if (!W_Pawn.textureready())
        return false;


    //if all load return 1
    return true;
}
