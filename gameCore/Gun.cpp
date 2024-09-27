#include "Gun.hpp"


Gun::Gun(float speed, float damage, float fireRate, int range)
	: speed(speed), damage(damage), fireRate(fireRate), range(range)
{
	texture.create(32, 16);
	texture.clear(sf::Color::Blue);
	setTexture(texture.getTexture());
	setOrigin(10, 8);
}


void Gun::shoot(sf::Vector2f point)
{
	sf::Vector2f direction = point - getPosition();
	
}