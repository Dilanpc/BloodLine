#include "Hud.hpp"


Hud::Hud(int windowWidth, int windowHeight)
{
	setSize(sf::Vector2f(windowWidth, windowHeight));
}

void Hud::update()
{

}

void Hud::draw(sf::RenderWindow& window)
{
	window.setView(*this);
	window.draw(ammo);
	window.draw(clipSize);
	window.draw(clip);
}