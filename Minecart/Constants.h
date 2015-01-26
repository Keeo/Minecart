#pragma once

struct Constants
{
	static const int CHUNK_SIZE = 20;
	static const int CUBE_TRESHOLD = 4; // z 64
	static const int MAP_SIZE = 16;
	static const int CHUNK_COUNT = MAP_SIZE * MAP_SIZE * MAP_SIZE;
	static const int RESOLUTION_X = 1024;
	static const int RESOLUTION_Y = 768;
};
