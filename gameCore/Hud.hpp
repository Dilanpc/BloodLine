#pragma once

#include <SFML/Graphics.hpp>

class Hud : public sf::View
{
public:
	Hud(int windowWidth, int windowHeight);

public:
	static sf::Font font;

	sf::Text ammo;
	sf::Text clipSize;
	sf::Text clip;


public:
	void update();
	// Change the view to the Hud view and draw the Hud
	void draw(sf::RenderWindow& window);


protected:
	

};