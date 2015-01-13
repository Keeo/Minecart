#include "stdafx.h"
#include "WorldBuilder.h"

namespace model
{

	boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>>* WorldBuilder::buildChunkMatrix()
	{
		boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>>* chunks = new boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>>(Constants::MAP_SIZE);

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			boost::circular_buffer<boost::circular_buffer<Chunk*>> temp(Constants::MAP_SIZE);
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				temp.push_back(boost::circular_buffer<Chunk*>(Constants::MAP_SIZE));
			}
			chunks->push_back(temp);
		}

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
					(*chunks)[i][j][k]->rebuildCubeVisibility();
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
