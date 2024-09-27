#pragma once

#include <SFML/Graphics.hpp>
#include "Gun.hpp"

class Player : protected sf::Sprite
{
private:
	static sf::RenderTexture texture; // Textura temporal

public:
	float speed = 3.0f;

protected:
	Gun* m_gun{};


public:
	Player();
	~Player();


public:
	void draw(sf::RenderWindow& window);

	void aim(const sf::Vector2f& point);
	void shoot(const sf::Vector2f& point);

	void move(int x, int y);
	
	void setPosition(float x, float y);
	using sf::Sprite::getPosition;

	void setGun(Gun* gun);
};