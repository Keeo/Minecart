#pragma once

struct Constants
{
#ifdef _DEBUG
	static const int CHUNK_SIZE = 32;
	static const int CUBE_TRESHOLD = 8; // z 64
	static const int MAP_SIZE = 1;
	static const int RESOLUTION_X = 1024;
	static const int RESOLUTION_Y = 768;
	static const bool SHOW_MOUSE = true;
	static const bool FULLSCREEN = false;
#else
	static const int CHUNK_SIZE = 32;
	static const int CUBE_TRESHOLD = 4; // z 64
	static const int MAP_SIZE = 5;
	static const int RESOLUTION_X = 1980;
	static const int RESOLUTION_Y = 1080;
	static const bool SHOW_MOUSE = false;
	static const bool FULLSCREEN = true;
#endif
	static const int CHUNK_COUNT = MAP_SIZE * MAP_SIZE * MAP_SIZE;
	static const int CUBE_EDGE = CHUNK_SIZE * MAP_SIZE;
};
