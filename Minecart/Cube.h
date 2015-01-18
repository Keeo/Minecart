#pragma once

#include "ECube.h"
#include <stdint.h>

namespace model
{

	struct Cube
	{
		ECube type;
		uint8_t dmg;
		uint8_t visible;

		Cube(){
			type = ECube::Dirt;
			dmg = 0;
			visible = 0;
		}

		inline bool isXPVisible() { return (visible & 0x20) != 0; }
		inline bool isXNVisible() { return (visible & 0x10) != 0; }
		inline bool isYPVisible() { return (visible & 0x08) != 0; }
		inline bool isYNVisible() { return (visible & 0x04) != 0; }
		inline bool isZPVisible() { return (visible & 0x02) != 0; }
		inline bool isZNVisible() { return (visible & 0x01) != 0; }
	};

}
