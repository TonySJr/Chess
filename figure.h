#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
class figure : Sprite
{
private:
	float m_column = 0;
	float m_row = 0;
	bool ok_flag = true;

public:
	Texture* m_texture = nullptr;
	Sprite* m_sprite = nullptr;
	figure(float col, float row, const char* texturepath)
		: m_column(col), m_row(row)
	{
		m_texture = new Texture;
		if (!m_texture->loadFromFile(texturepath))
		{
			std::cout << "load Texture fail" << std::endl;
			ok_flag = false;
		}
		m_sprite = new Sprite;
		m_sprite->setTexture(*m_texture);
		m_sprite->scale(2.f, 2.f);
		m_sprite->setPosition(col*64.f, row*64.f);
	}

	figure(const char* boardtexture)
	{
		m_texture = new Texture;
		if (!m_texture->loadFromFile(boardtexture))
		{
			std::cout << "board Texture fail" << std::endl;
			ok_flag = false;\
		}
		m_sprite = new Sprite;
		m_sprite->setTexture(*m_texture);
	}

	~figure()
	{
		std::cout << "Figure destroyed" << std::endl;
		delete m_sprite;
		delete m_texture;
	}

	Sprite& spritefigure();
	bool textureready() const;
	void setPos(float x, float y);
};
/*
class figureRes : Sprite
{
public:
	figureRes(class Sprite& sprite,float x,float y)
	{
		sprite.setPosition(x * 64.f,y * 64.f);
	}
	~figureRes()
	{

	}
};
*/

