#include "Player.hpp"

sf::RenderTexture Player::texture; // Textura temporal


Player::Player()
{
	//Textura temporal
	texture.create(32, 32);
	texture.clear(sf::Color::Green);

	setTexture(texture.getTexture());
	setOrigin(16, 16);

	m_gun = new Gun(10, 10, 1, 60);
	m_gun->setPosition(getPosition());
}

Player::~Player()
{
	delete m_gun;
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(*this);
	window.draw(*m_gun);
}

void Player::move(int x, int y)
{
	float mag = sqrt(x * x + y * y);
	if (mag != 0) {
		sf::Sprite::move(x * speed / mag, y * speed / mag);
		m_gun->move(x * speed / mag, y * speed / mag);
	}

}

void Player::setPosition(float x, float y)
{
	sf::Sprite::setPosition(x, y);
	m_gun->setPosition(x, y);
}

void Player::setGun(Gun* gun)
{
	delete m_gun;
	m_gun = gun;
}