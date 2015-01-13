#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

struct GameTime {

	float asSeconds() const {
		return time.asSeconds();
	}

	float getTotalElapsedTime() const {
		return totalTime.getElapsedTime().asSeconds();
	}

	sf::Time time;
	sf::Clock totalTime;
};

