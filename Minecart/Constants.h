#pragma once

struct Constants
{
	static const int CHUNK_SIZE = 32;
	static const int CUBE_TRESHOLD = 7; // z 64
	static const int MAP_SIZE = 8;
	static const int CHUNK_COUNT = MAP_SIZE * MAP_SIZE * MAP_SIZE;
	static const int RESOLUTION_X = 1024;
	static const int RESOLUTION_Y = 768;
};
