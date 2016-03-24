#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "musicplayer.h"

void checkEvents(sf::Event & e, sf::RenderWindow & window, MusicPlayer & gameMusic);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Music Player Driver");
	window.setFramerateLimit(60);
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	MusicPlayer gameMusic;

	gameMusic.loadPaths();
	gameMusic.setMaxVolume(100.f);
	gameMusic.setFadeSpeed(sf::seconds(2.f));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			try
			{
				checkEvents(event, window, gameMusic);
			}
			catch (std::runtime_error & ex)
			{
				std::cout << ex.what() << std::endl;
				return 1;
			}
		}

		gameMusic.update(timePerFrame);

		window.clear(sf::Color::Black);
		window.display();
	}

	return 0;
}

void checkEvents(sf::Event & e, sf::RenderWindow & window, MusicPlayer & gameMusic)
{
	switch (e.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::A)
		{
			gameMusic.play(MusicIdentifier::TITLE_SCREEN);
		}
		else if (e.key.code == sf::Keyboard::S)
		{
			gameMusic.play(MusicIdentifier::GAME);
		}
		else if (e.key.code == sf::Keyboard::D)
		{
			gameMusic.stop();
		}
		else if (e.key.code == sf::Keyboard::Q)
		{
			gameMusic.setVolumeFading(false);
		}
		else if (e.key.code == sf::Keyboard::W)
		{
			gameMusic.setVolumeFading(true);
		}
		else if (e.key.code == sf::Keyboard::V)
		{
			std::cout << "DEBUG:\n\tMax Music Player Volume: " << gameMusic.getMaxVolume() << std::endl;
		}
		else if (e.key.code == sf::Keyboard::F)
		{
			std::cout << "DEBUG:\n\tMusic Player Fade Speed: " << gameMusic.getFadeSpeed().asSeconds() << " seconds\n";
		}
		else if (e.key.code == sf::Keyboard::B)
		{
			std::cout << "DEBUG:\n\tMusic Player Fading Active (0 off, 1 on): " << gameMusic.getVolumeFading() << std::endl;
		}
		break;
	}
}