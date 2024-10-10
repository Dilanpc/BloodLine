#include "BloodLine.hpp"

#include <iostream>

BloodLine::BloodLine()
{
}
BloodLine::~BloodLine()
{
	delete player;
	delete camera;
	delete bulletManager;
	delete hud;
}



void BloodLine::start()
{
	// Initialize variables
	player = new Player();
	camera = new sf::View();
	bulletManager = new BulletManager();
	hud = new Hud(windowWidth, windowHeight);
	background = new Background();

	Gun::setBulletManager(bulletManager);


	m_window.create(sf::VideoMode(windowWidth, windowHeight), "BloodLine", sf::Style::Close);
	camera->setSize(windowWidth, windowHeight);
	sf::Clock clock;

	player->setGun(new Gun(10, 10, 8, 800, 20, 200, sf::seconds(2)));
	player->setPosition(100, 100);
	

	background->setPosition(0, 0);

	sf::Vector2<int8_t> direction(0, 0); // keyword input
	bool lclick = false;
	sf::Vector2f mousePos;

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();

			// Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W) direction.y = -1;
				if (event.key.code == sf::Keyboard::S) direction.y = 1;
				if (event.key.code == sf::Keyboard::A) direction.x = -1;
				if (event.key.code == sf::Keyboard::D) direction.x = 1;

				if (event.key.code == sf::Keyboard::R) player->startReload();
			}

			// Key Released
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::W) direction.y = 0;
				if (event.key.code == sf::Keyboard::S) direction.y = 0;
				if (event.key.code == sf::Keyboard::A) direction.x = 0;
				if (event.key.code == sf::Keyboard::D) direction.x = 0;
			}
			
			// Mouse
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					lclick = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					lclick = false;
				}
			}
		}



		player->move(direction.x, direction.y);


		camera->setCenter(player->getPosition());
		m_window.setView(*camera);

		// Mouse position
		mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

		if (lclick)
		{
			player->shoot(mousePos);
		}

		// Update
		bulletManager->update();
		player->update(mousePos);


		m_window.clear();
		m_window.draw(*background);
		player->draw(m_window);
		bulletManager->draw(m_window);
		m_window.display();

		sf::sleep(sf::milliseconds(1000 / 60) - clock.getElapsedTime()); // 60 fps
		clock.restart();
	}

}