#include "pch.h"
#include "FigureNames.h"
#include "figure.h"
#include "functions.h"
using namespace sf;

void draw(class RenderWindow& window)
{
    window.clear(Color::Black);
    // draw board
    window.draw(Board.spritefigure());
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLUMS; x++)
        {
            switch (ChessBoard[x + y*ROWS])
            {
            case 't':
            {
                B_Rook.setPos((float)x, (float)y);
                window.draw(B_Rook.spritefigure());
                break;
            }
            case 'l':
            {
                B_Knight.setPos((float)x, (float)y);
                window.draw(B_Knight.spritefigure());
                break;
            }
            case 's':
            {
                B_Bishop.setPos((float)x, (float)y);
                window.draw(B_Bishop.spritefigure());
                break;
            }
            case 'f':
            {
                B_Queen.setPos((float)x, (float)y);
                window.draw(B_Queen.spritefigure());
                break;
            }
            case 'k':
            {
                B_King.setPos((float)x, (float)y);
                window.draw(B_King.spritefigure());
                break;
            }
            case 'p':
            {
                B_Pawn.setPos((float)x, (float)y);
                window.draw(B_Pawn.spritefigure());
                break;
            }

            case 'T':
            {
                W_Rook.setPos((float)x, (float)y);
                window.draw(W_Rook.spritefigure());
                break;
            }
            case 'L':
            {
                W_Knight.setPos((float)x, (float)y);
                window.draw(W_Knight.spritefigure());
                break;
            }
            case 'S':
            {
                W_Bishop.setPos((float)x, (float)y);
                window.draw(W_Bishop.spritefigure());
                break;
            }
            case 'F':
            {
                W_Queen.setPos((float)x, (float)y);
                window.draw(W_Queen.spritefigure());
                break;
            }
            case 'K':
            {
                W_King.setPos((float)x, (float)y);
                window.draw(W_King.spritefigure());
                break;
            }
            case 'P':
            {
                W_Pawn.setPos((float)x, (float)y);
                window.draw(W_Pawn.spritefigure());
                break;
            }
            default:
                break;
            }
        }
    }
    // end the current frame
    window.display();
    
}

int button_delay = 0;
bool button_flag = true;
Vector2i prevPosition, newPosition;
void mouseShedule(class RenderWindow& window)
{
    if (Mouse::isButtonPressed(Mouse::Left))
    {

        if (button_delay > 1000)
        {
            // get the local mouse position (relative to a window)
            if (button_flag == true)
            {
                button_flag = false;
                prevPosition = (Mouse::getPosition(window)); // window is a sf::Window
                prevPosition.x = prevPosition.x >> 6; // delenie na 64
                prevPosition.y = prevPosition.y >> 6;
                button_delay = 0;
                std::cout << "Button True\n";
            }
            else
            {
                newPosition = (Mouse::getPosition(window));
                newPosition.x = newPosition.x >> 6;
                newPosition.y = newPosition.y >> 6;
                Swap(ChessBoard,prevPosition.x, prevPosition.y, newPosition.x, newPosition.y);
                button_flag = true;
                AI_turn_flag = true;
                button_delay = 0;
                std::cout << "Button false\n";
            }
        }
    }
    button_delay++;
    if (button_delay > 100000) button_delay = 0;
}