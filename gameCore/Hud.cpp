#include "Hud.hpp"
#include "Player.hpp"

const std::string Hud::fontPath = "resources/fonts/HTOWERT.TTF";
sf::Font Hud::font;


Hud::Hud(int windowWidth, int windowHeight)
{
	setSize(sf::Vector2f(windowWidth, windowHeight));
	setCenter(windowWidth / 2.f, windowHeight / 2.f);
	ammo.setFont(font);
	clipSize.setFont(font);
	clip.setFont(font);

	ammo.setCharacterSize(25);
	ammo.setFillColor(sf::Color::White);
	ammo.setPosition(35, windowHeight - 40);


	clipSize.setCharacterSize(25);
	clipSize.setFillColor(sf::Color::White);
	clipSize.setPosition(60, windowHeight - 60);

	clip.setCharacterSize(60);
	clip.setFillColor(sf::Color::White);
	clip.setPosition(10, windowHeight - 100);

}

void Hud::loadFont()
{
	font.loadFromFile(fontPath);
}

void Hud::update()
{
	const Gun* gun = *m_gun;
	ammo.setString(std::to_string(gun->getAmmo()));
	clip.setString(std::to_string(gun->getClip()));
	clipSize.setString(std::to_string(gun->getClipSize()));

	//ammo.setString("Ammo");
	//clip.setString("Clip");
	//clipSize.setString("Size");
}

void Hud::setPlayer(const Player* player)
{
	m_gun = player->_getGunDirection();
}

void Hud::draw(sf::RenderWindow& window)
{
	window.setView(*this);
	window.draw(ammo);
	window.draw(clipSize);
	window.draw(clip);
}