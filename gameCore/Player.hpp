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
	void updateReload(); // Check if the reload is done

	void move(int x, int y);

	void update(const sf::Vector2f& point); // Aims and updates the reload
	
	void setPosition(float x, float y);
	using sf::Sprite::getPosition;

	void setGun(Gun* gun);
	Gun* getGun() const;
	const Gun* const* _getGunDirection() const; // Returns the direction of internal gun pointer (for Hud) (&m_gun)
};