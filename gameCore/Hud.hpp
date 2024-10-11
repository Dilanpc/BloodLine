#pragma once

#include <SFML/Graphics.hpp>

class Player;
class Gun;

class Hud : public sf::View
{
public:
	Hud(int windowWidth, int windowHeight);

// Font
public:
	static sf::Font font;
	static void loadFont();
private:
	static const std::string fontPath;




public:
	sf::Text ammo;
	sf::Text clipSize;
	sf::Text clip;

private:
	const Gun* const* m_gun{};
public:
	// Takes the gun from the player as a double pointer; if the player changes the gun, the Hud will change too
	void setPlayer(const Player* player);



public:
	void update();
	// Change the view to the Hud view and draw the Hud
	void draw(sf::RenderWindow& window);


};