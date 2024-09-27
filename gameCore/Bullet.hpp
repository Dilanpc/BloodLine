#include <SFML/Graphics.hpp>
#include <list>

class Bullet : public sf::CircleShape
{
public:
	Bullet(const sf::Vector2f& position, const sf::Vector2f& velocity, float distance);

public:
	void update();

	bool isAlive() const { return m_timeAlive < m_maxTimeAlive; }

private:
	sf::Vector2f m_velocity;
	unsigned int m_maxTimeAlive;
	unsigned int m_timeAlive = 0;
	
};




class BulletManager
{
public:
	BulletManager();

public:
	void update();
	void draw(sf::RenderWindow& window);
	void addBullet(const sf::Vector2f& position, const sf::Vector2f& velocity, float distance);

public:
	std::list<Bullet> bullets;

};
