#include "Background.hpp"


Background::Background()
{
	texture.create(800, 600);
	texture.clear(sf::Color(0x444444ff));
	setTexture(texture.getTexture());
}