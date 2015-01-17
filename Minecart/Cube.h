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

		bool isXPVisible() { return (visible & 0x20) != 0; }
		bool isXNVisible() { return (visible & 0x10) != 0; }
		bool isYPVisible() { return (visible & 0x08) != 0; }
		bool isYNVisible() { return (visible & 0x04) != 0; }
		bool isZPVisible() { return (visible & 0x02) != 0; }
		bool isZNVisible() { return (visible & 0x01) != 0; }
	};

}
