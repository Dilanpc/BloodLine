#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.hpp"

class Gun : public sf::Sprite
{
public:
	Gun(float speed, float damage, float fireRate, int range, unsigned int clipSize, unsigned int ammo, sf::Time reloadTime);

public:
	void shoot(sf::Vector2f point);
	void startReload(); // Resets the reload clock
	bool reload(); // Tries to reload, returns true if the reload is done

	static void setBulletManager(BulletManager* bulletManager);

protected:
	float speed;
	float damage;
	float fireRate;
	float range; // Distance the bullet can travel

	unsigned int clipSize;
	unsigned int clip;
	unsigned int ammo;

	sf::Time m_reloadTime;

public:
	unsigned int getClipSize() const;
	void setClipSize(unsigned int clipSize);
	unsigned int getClip() const;
	void setClip(unsigned int clip);
	unsigned int getAmmo() const;
	void setAmmo(unsigned int ammo);

private:
	sf::RenderTexture texture; // Temp

	static BulletManager* bulletManager;

	sf::Clock m_clock; // Used to calculate the cooldown between shots
	sf::Time m_cooldown;

	sf::Clock m_reloadClock; // Used to calculate the time between reloads
};