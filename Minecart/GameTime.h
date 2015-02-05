#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

struct GameTime
{

	inline float asSeconds() const {
		return time.asSeconds();
	}

	inline float getTotalElapsedTime() const {
		return totalTime.getElapsedTime().asSeconds();
	}

	sf::Time time;
	sf::Clock totalTime;
};

