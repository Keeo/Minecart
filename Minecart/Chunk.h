#pragma once

#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/type_precision.hpp>

#include "Constants.h"
#include "Utils.h"
#include "Drawable.h"
#include "Cube.h"
#include "IEventMessagingSystem.h"
#include "SimplexNoise.h"

namespace model
{

	class Chunk : public view::Drawable, public IEventMessagingSystem
	{

		Cube cubes_[Constants::CHUNK_SIZE][Constants::CHUNK_SIZE][Constants::CHUNK_SIZE];
		glm::i32vec3 position_;
		glm::vec3 center_;


		// surounding chunks
		Chunk* u = 0;
		Chunk* d = 0;
		
		Chunk* w = 0;
		Chunk* e = 0;

		Chunk* n = 0;
		Chunk* s = 0;

		void loadCubes();

	public:
		bool putCube(glm::i32vec3 pos, ECube cube = ECube::Air);
		ECube getCube(const glm::i32vec3& pos);

		void setNeighbors(Chunk* up, Chunk* down, Chunk* east, Chunk* west, Chunk* north, Chunk* south);
		void init(glm::i32vec3 position);

		const glm::i32vec3* getPosition() const;
		const glm::vec3* getCenter() const;

		bool assertLinks();

		void rebuildOneCubeChangeVisibility(glm::i32vec3 local);
		inline void rebuildCubeVisibility(int i, int j, int k);
		void rebuildCubesVisibilityEdge(EDirection edge);
		void rebuildCubesVisibilityCore();
		void rebuildCubesVisibility();

		Cube(&getCubes())[Constants::CHUNK_SIZE][Constants::CHUNK_SIZE][Constants::CHUNK_SIZE];

		Chunk(glm::i32vec3 position);

		~Chunk();

	};

	struct DistancePred
	{
		DistancePred(glm::vec3 p) : pos(p) { }
		bool operator()(const Chunk* a, const Chunk* b) {
			return glm::distance(pos, *a->getCenter()) < glm::distance(pos, *b->getCenter());

		}
		const glm::vec3 pos;
	};

}