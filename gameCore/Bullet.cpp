#include "Bullet.hpp"


Bullet::Bullet(float x, float y, sf::Vector2f velocity)
{
	setRadius(5);
	setFillColor(sf::Color::White);
	setPosition(x, y);
	m_velocity = velocity;
}

void Bullet::update()
{
	move(m_velocity);
}










BulletManager::BulletManager()
{
}


void BulletManager::update()
{
	for (Bullet& bullet : bullets)
	{
		bullet.update();
	}
}

void BulletManager::draw(sf::RenderWindow& window)
{
	for (Bullet& bullet : bullets)
	{
		window.draw(bullet);
	}
}

void BulletManager::addBullet(float x, float y, sf::Vector2f velocity)
{
	bullets.emplace_back(x, y, velocity);
}