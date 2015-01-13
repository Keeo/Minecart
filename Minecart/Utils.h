#pragma once

#include "Constants.h"

class Utils
{
public:
	inline static int worldMod(int x) {
		return ((x % Constants::MAP_SIZE) + Constants::MAP_SIZE) % Constants::MAP_SIZE;
	}
};

