#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//bool LoadTexture();
bool InitTextures();
void draw(class RenderWindow& example);
void mouseShedule(class RenderWindow& example);
void Swap(char*arr,int x1,int y1, int x2, int y2);
//	AI things
void AI_Main_Function();