#pragma once

#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/type_precision.hpp>

#include "Constants.h"
#include "Drawable.h"
#include "Cube.h"

namespace model
{

	class Chunk : public view::Drawable
	{

		Cube cubes_[Constants::CHUNK_SIZE][Constants::CHUNK_SIZE][Constants::CHUNK_SIZE];
		glm::i32vec3 position_;
		glm::vec3 center_;


		// surounding chunks
		Chunk* u = 0;
		Chunk* d = 0;
		Chunk* n = 0;
		Chunk* w = 0;
		Chunk* e = 0;
		Chunk* s = 0;

	public:

		void setNeighbors(Chunk* up, Chunk* down, Chunk* north, Chunk* west, Chunk* east, Chunk* south);

		const glm::i32vec3* getPosition() const;
		const glm::vec3* getCenter() const;

		void assertLinks();

		inline void rebuildCubeVisibility(int i, int j, int k);
		void rebuildCubesVisibilityEdge(EDirection edge);
		void rebuildCubesVisibilityCore();
		void rebuildCubesVisibility();

		Cube(&getCubes())[Constants::CHUNK_SIZE][Constants::CHUNK_SIZE][Constants::CHUNK_SIZE];

		Chunk(glm::i32vec3 position);

		~Chunk();

	};

	class DistancePred
	{
	public:
		DistancePred(glm::vec3 p) : pos(p) { }
		bool operator()(const Chunk* a, const Chunk* b) {
			return glm::distance(pos, *a->getCenter()) < glm::distance(pos, *b->getCenter());

		}
	private:
		const glm::vec3 pos;
	};

}