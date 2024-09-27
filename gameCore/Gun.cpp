#include "Gun.hpp"
#include <iostream>
BulletManager* Gun::bulletManager = nullptr;

Gun::Gun(float speed, float damage, float fireRate, int range)
	: speed(speed), damage(damage), fireRate(fireRate), range(range)
{
	texture.create(32, 16);
	texture.clear(sf::Color::Blue);
	setTexture(texture.getTexture());
	setOrigin(10, 8);

	m_cooldown = sf::seconds(1 / fireRate);
}


void Gun::shoot(sf::Vector2f point)
{
	if (m_clock.getElapsedTime() > m_cooldown)
	{
		m_clock.restart();

		sf::Vector2f direction = point - getPosition();
		float mag = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= mag;

		bulletManager->addBullet(getPosition(), direction * speed, range);
	}
}


void Gun::setBulletManager(BulletManager* bulletManager)
{
	Gun::bulletManager = bulletManager;
}