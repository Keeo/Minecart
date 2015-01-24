#include "stdafx.h"
#include "WorldBuilder.h"

namespace model
{

	WorldBuilder::WorldBuilder()
	{
		Register(EEvent::FillChunks, this, (model::Callback) & WorldBuilder::fillChunks);
		Register(EEvent::RebuildVisbility, this, (model::Callback) & WorldBuilder::rebuildVisibility);
	}

	TripleChunkBuffer* WorldBuilder::buildChunkMatrix()
	{
		TripleChunkBuffer* chunks = new TripleChunkBuffer(Constants::MAP_SIZE);

		fillChunks(chunks);
		chunks->relink();
		rebuildVisibility(chunks);
		
		return chunks;
	}

	void WorldBuilder::fillChunks(TripleChunkBuffer* chunks)
	{
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					(*chunks)[i][j].push_back(new Chunk(glm::i32vec3(i, j, k) * Constants::CHUNK_SIZE));
				}
			}
		}
	}

	void WorldBuilder::rebuildVisibility(TripleChunkBuffer* chunks)
	{
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
	}

	WorldBuilder::~WorldBuilder()
	{
	}

}
