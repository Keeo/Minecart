#include "stdafx.h"
#include "WorldBuilder.h"

namespace model
{

	TripleChunkBuffer* WorldBuilder::buildChunkMatrix()
	{
		TripleChunkBuffer* chunks = new TripleChunkBuffer(Constants::MAP_SIZE);

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					(*chunks)[i][j].push_back(new Chunk(glm::i32vec3(i, j, k) * Constants::CHUNK_SIZE));
				}
			}
		}

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					Chunk& c = *(*chunks)[i][j][k];
					c.setNeighbors(
						(*chunks)[i][Utils::worldMod(j + 1)][k],
						(*chunks)[i][Utils::worldMod(j - 1)][k],

						(*chunks)[Utils::worldMod(i + 1)][j][k],
						(*chunks)[Utils::worldMod(i - 1)][j][k],

						(*chunks)[i][j][Utils::worldMod(k + 1)],
						(*chunks)[i][j][Utils::worldMod(k - 1)]
						);
				}
			}
		}

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					(*chunks)[i][j][k]->assertLinks();
				}
			}
		}

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					//(*chunks)[i][j][k]->rebuildCubesVisibility();
					(*chunks)[i][j][k]->rebuildCubesVisibilityEdge(EDirection::UP);
					(*chunks)[i][j][k]->rebuildCubesVisibilityEdge(EDirection::DOWN);

					(*chunks)[i][j][k]->rebuildCubesVisibilityEdge(EDirection::LEFT);
					(*chunks)[i][j][k]->rebuildCubesVisibilityEdge(EDirection::RIGHT);

					(*chunks)[i][j][k]->rebuildCubesVisibilityEdge(EDirection::FORWARD);
					(*chunks)[i][j][k]->rebuildCubesVisibilityEdge(EDirection::BACKWARD);
				}
			}
		}

		return chunks;
	}

	WorldBuilder::WorldBuilder()
	{
	}


	WorldBuilder::~WorldBuilder()
	{
	}

}
