#include "Player.hpp"

#include <iostream>

sf::RenderTexture Player::texture; // Textura temporal


Player::Player()
{
	//Textura temporal
	texture.create(32, 32);
	texture.clear(sf::Color::Green);

	setTexture(texture.getTexture());
	setOrigin(16, 16);

	m_gun = new Gun(10, 10, 1, 50, 10, 100, sf::seconds(2)); // Temporal gun
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

void Player::aim(const sf::Vector2f& point)
{
	m_gun->setRotation(atan2(point.y - getPosition().y, point.x - getPosition().x) * 180 / 3.14159265);
}

void Player::shoot(const sf::Vector2f& point)
{
	if (!m_reloading)
		m_gun->shoot(point);
}

void Player::startReload()
{
	if (!m_reloading) {
		m_reloading = true;
		m_gun->startReload();
	}
}

void Player::updateReload()
{
	if (m_gun->reload()) // Verify if the reload is done
		m_reloading = false;
}

void Player::move(int x, int y)
{
	float mag = sqrt(x * x + y * y);
	if (mag != 0) {
		sf::Sprite::move(x * speed / mag, y * speed / mag);
		m_gun->move(x * speed / mag, y * speed / mag);
	}

}

void Player::update(const sf::Vector2f& point)
{
	aim(point);
	if (m_reloading)
		updateReload();
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
	m_gun->setPosition(getPosition());
}

Gun* Player::getGun() const
{
	return m_gun;
}

const Gun* const* Player::_getGunDirection() const
{
	return &m_gun;
}