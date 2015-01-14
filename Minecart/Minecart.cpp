// Minecart.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Controller.h"
#include "Chunk.h"
#include "Window.h"
#include <glm/gtc/noise.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
	/*model::Chunk u(glm::i32vec3(0));
	model::Chunk d(glm::i32vec3(0));

	model::Chunk n(glm::i32vec3(0));
	model::Chunk w(glm::i32vec3(0));

	model::Chunk e(glm::i32vec3(0));
	model::Chunk s(glm::i32vec3(0));

	model::Chunk c(glm::i32vec3(0));
	auto cc = c.getCubes();
	c.setNeighbors(&u, &d, &n, &w, &e, &s);

	auto uc = u.getCubes();
	uc[16][0][16].type = ECube::Air;

	c.rebuildCubeVisibility();
	assert(cc[16][31][16].isYPVisible());

	auto dc = d.getCubes();
	dc[16][31][16].type = ECube::Air;

	c.rebuildCubeVisibility();
	assert(cc[16][0][16].isYNVisible());



	auto wc = w.getCubes();
	wc[31][16][16].type = ECube::Air;

	c.rebuildCubeVisibility();
	assert(cc[0][16][16].isXNVisible());

	auto ec = e.getCubes();
	ec[0][16][16].type = ECube::Air;

	c.rebuildCubeVisibility();
	assert(cc[31][16][16].isXPVisible());


	auto nc = n.getCubes();
	nc[16][16][0].type = ECube::Air;

	c.rebuildCubeVisibility();
	assert(cc[16][16][31].isZPVisible());

	auto sc = s.getCubes();
	sc[16][16][31].type = ECube::Air;

	c.rebuildCubeVisibility();
	assert(cc[16][16][0].isZNVisible());*/


	Controller* c = new Controller();
	c->run();
	return 0;
}

