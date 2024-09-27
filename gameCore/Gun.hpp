#pragma once

#include <SFML/Graphics.hpp>

class Gun : public sf::Sprite
{
public:
	Gun(float speed, float damage, float fireRate, int range);

public:
	void shoot(sf::Vector2f point);

public:
	float speed;
	float damage;
	float fireRate;
	int range; // Tiempo frames

protected:
	sf::RenderTexture texture; // Temporal
};