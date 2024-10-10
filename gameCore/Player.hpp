#pragma once

#include <SFML/Graphics.hpp>
#include "Gun.hpp"

class Player : protected sf::Sprite
{
private:
	static sf::RenderTexture texture; // Textura temporal

public:
	float speed = 3.0f;

private:
	Gun* m_gun{};

	bool m_reloading = false;


public:
	Player();
	~Player();


public:
	void draw(sf::RenderWindow& window);

	void aim(const sf::Vector2f& point);
	void shoot(const sf::Vector2f& point);
	void startReload();
	void updateReload(); // Verify if the reload is done

	void move(int x, int y);

	void update(const sf::Vector2f& point); // Aim and update reload
	
	void setPosition(float x, float y);
	using sf::Sprite::getPosition;

	void setGun(Gun* gun);
};