#include "BloodLine.hpp"
#include "Hud.hpp"
#include "Background.hpp"


BloodLine::BloodLine()
{
}



void BloodLine::start()
{
	m_window.create(sf::VideoMode(windowWidth, windowHeight), "BloodLine", sf::Style::Close);
	camera.setSize(windowWidth, windowHeight);
	sf::Clock clock;


	player.setPosition(100, 100);
	Hud hud(windowWidth, windowHeight);
	Background background;
	background.setPosition(0, 0);

	sf::Vector2<int8_t> direction(0, 0); // Usado para guardar inputs de teclas

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
			}

			// Key Released
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::W) direction.y = 0;
				if (event.key.code == sf::Keyboard::S) direction.y = 0;
				if (event.key.code == sf::Keyboard::A) direction.x = 0;
				if (event.key.code == sf::Keyboard::D) direction.x = 0;
			}
		}



		player.move(direction.x, direction.y);


		camera.setCenter(player.getPosition());
		m_window.setView(camera);


		m_window.clear();
		m_window.draw(background);
		player.draw(m_window);
		m_window.display();

		sf::sleep(sf::milliseconds(1000 / 60) - clock.getElapsedTime()); // Configurado a 60 fps
		clock.restart();
	}

}