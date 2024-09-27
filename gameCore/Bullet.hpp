#include <SFML/Graphics.hpp>
#include <list>

class Bullet : public sf::CircleShape
{
public:
	Bullet(float x, float y, sf::Vector2f velocity);

public:
	void update();

private:
	sf::Vector2f m_velocity;
	
};




class BulletManager
{
public:
	BulletManager();

public:
	void update();
	void draw(sf::RenderWindow& window);
	void addBullet(float x, float y, sf::Vector2f velocity);

public:
	std::list<Bullet> bullets;

};
