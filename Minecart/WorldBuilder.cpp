#include "stdafx.h"
#include "WorldBuilder.h"

namespace model
{

	WorldBuilder::WorldBuilder()
	{
		Register(EEvent::FillChunks, this, (model::Callback) & WorldBuilder::fillChunks);
		Register(EEvent::RebuildVisbility, this, (model::Callback) & WorldBuilder::rebuildVisibility);
		Register(EEvent::InitSequence, this, (model::Callback) & WorldBuilder::initSequence);
	}

	TripleChunkBuffer* WorldBuilder::buildChunkMatrix()
	{
		TripleChunkBuffer* tcb = new TripleChunkBuffer(Constants::MAP_SIZE);

		fillChunks(tcb);
		tcb->relink();
		Post(EEvent::PG_BuildVisibility, tcb, 0);
		
		return tcb;
	}

	void WorldBuilder::initSequence(void* data)
	{
		TripleChunkBuffer** c = (TripleChunkBuffer**)data;
		TripleChunkBuffer* tcb = buildChunkMatrix();
		*c = tcb;
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
					(*chunks)[i][j][k]->rebuildCubesVisibility();
				}
			}
		}
	}

	WorldBuilder::~WorldBuilder()
	{
	}

}
