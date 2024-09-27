#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.hpp"

class Gun : public sf::Sprite
{
public:
	Gun(float speed, float damage, float fireRate, int range);

public:
	void shoot(sf::Vector2f point);

	static void setBulletManager(BulletManager* bulletManager);

public:
	float speed;
	float damage;
	float fireRate;
	float range; // Distance the bullet can travel

protected:
	sf::RenderTexture texture; // Temp

	static BulletManager* bulletManager;

	sf::Clock m_clock;
	sf::Time m_cooldown;
};