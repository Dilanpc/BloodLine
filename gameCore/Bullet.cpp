#include "Bullet.hpp"


Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& velocity, float distance)
	: m_velocity(velocity)
{
	setRadius(5);
	setFillColor(sf::Color::Yellow);
	setPosition(position);

	float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y); // magnitude of the velocity
	m_maxTimeAlive = distance / speed; // amount of frames to reach the distance

}

void Bullet::update()
{
	move(m_velocity);
	m_timeAlive++;
}










BulletManager::BulletManager()
{
}


void BulletManager::update()
{
	for (auto it = bullets.begin(); it != bullets.end(); )
	{
		it->update();
		if (!it->isAlive()) {
			it = bullets.erase(it);
		}
		else {
			++it;
		}
	}
}

void BulletManager::draw(sf::RenderWindow& window)
{
	for (Bullet& bullet : bullets)
	{
		window.draw(bullet);
	}
}

void BulletManager::addBullet(const sf::Vector2f& position, const sf::Vector2f& velocity, float distance)
{
	bullets.emplace_back(position, velocity, distance);
}