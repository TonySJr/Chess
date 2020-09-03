#include "pch.h"
#include "FigureNames.h"
#include "functions.h"
#include "figure.h"

#define WindowWidth 512
#define WindowHeight 512

using namespace sf;

void Swap(char* arr,int x1, int y1, int x2, int y2)
{
    std::cout << x1 << " " << y1 << std::endl;
    std::cout << x2 << " " << y2 << std::endl;
    //char temp = ChessBoard[y1][x1];
    //ChessBoard[y1][x1] = ChessBoard[y2][x2];
    //ChessBoard[y2][x2] = temp;
    arr[x2 + y2 * ROWS] = arr[x1 + y1 * ROWS];
    arr[x1 + y1 * ROWS] = '0';
}
int main()
{

    // create the window
    RenderWindow window(VideoMode(WindowWidth, WindowHeight), "Chess");
      
    if (!InitTextures()) return 0;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        mouseShedule(window);

        draw(window);
        //aiturn
        if (AI_turn_flag == true)
        {
            std::cout << "AI Turn \n";
            AI_Main_Function();
        }

    }

    return 0;
}