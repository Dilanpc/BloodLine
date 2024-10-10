#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Background.hpp"
#include "Hud.hpp"


class BloodLine
{
public:
	BloodLine();
	~BloodLine();
	
protected:
	static const int windowWidth = 1280;
	static const int windowHeight = 720;
	Player* player{};
	sf::View* camera{};

	BulletManager* bulletManager{};

	Hud* hud{};
	Background* background{};




public:
	void start();

protected:
	sf::RenderWindow m_window;



};