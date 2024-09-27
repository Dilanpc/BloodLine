#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"


class BloodLine
{
public:
	BloodLine();
	
protected:
	static const int windowWidth = 1280;
	static const int windowHeight = 720;
	Player player;
	sf::View camera;



public:
	void start();

protected:
	sf::RenderWindow m_window;



};