#include "Gun.hpp"


BulletManager* Gun::bulletManager = nullptr;

Gun::Gun(float speed, float damage, float fireRate, int range, unsigned int clipSize, unsigned int ammo, sf::Time reloadTime)
	: speed(speed), damage(damage), fireRate(fireRate), range(range), clipSize(clipSize), clip(clipSize), ammo(ammo)
	, m_reloadTime(reloadTime)
{
	texture.create(32, 16);
	texture.clear(sf::Color::Blue);
	setTexture(texture.getTexture());
	setOrigin(10, 8);

	m_cooldown = sf::seconds(1 / fireRate);
}


void Gun::shoot(sf::Vector2f point)
{
	if (m_clock.getElapsedTime() > m_cooldown && clip > 0)
	{
		m_clock.restart();

		sf::Vector2f direction = point - getPosition();
		float mag = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= mag;
		
		bulletManager->addBullet(getPosition(), direction * speed, range);

		clip--;
	}
}

void Gun::startReload()
{
	m_reloadClock.restart();
}

bool Gun::reload()
{
	if (m_reloadClock.getElapsedTime() > m_reloadTime && clip < clipSize && ammo > 0)
	{
		m_reloadClock.restart();
		if (ammo > clipSize - clip)
		{
			ammo -= clipSize - clip;
			clip = clipSize;
		}
		else
		{
			clip += ammo;
			ammo = 0;
		}
		return true;
	}
	if (clip == clipSize || ammo == 0)
	{
		return true;
	}
	return false;
}


void Gun::setBulletManager(BulletManager* bulletManager)
{
	Gun::bulletManager = bulletManager;
}