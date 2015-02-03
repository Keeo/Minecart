#include "stdafx.h"
#include "WorldBuilder.h"

namespace model
{

	WorldBuilder::WorldBuilder()
	{
		Register(EEvent::FillChunks, this, (model::Callback) & WorldBuilder::fillChunks);
		Register(EEvent::RebuildVisbility, this, (model::Callback) & WorldBuilder::rebuildVisibility);
		Register(EEvent::InitSequence, this, (model::Callback) & WorldBuilder::initSequence);
		Register(EEvent::GenerateAndMoveSlice, this, (model::Callback) & WorldBuilder::generateSlice);
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
	void WorldBuilder::generateSlice(void** data)
	{
		auto tcb = (model::TripleChunkBuffer*)data[0];
		EDirection& ed = *(EDirection*)data[1];

		std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* chunks = tcb->read(ed);

		const glm::i32vec3 pivot = *(*tcb)
			[ed == LEFT || ed == RIGHT ? Constants::MAP_SIZE - 1 : 0]
		[ed == UP || ed == DOWN ? Constants::MAP_SIZE - 1 : 0]
		[ed == FORWARD || ed == BACKWARD ? Constants::MAP_SIZE - 1 : 0]
		->getPosition();

		if (ed == UP || ed == DOWN) {
			for (int i = 0; i < Constants::MAP_SIZE; ++i) {
				for (int j = 0; j < Constants::MAP_SIZE; ++j) {
					glm::i32vec3 p(i, ed == UP ? 1 : -Constants::MAP_SIZE, j);
					p *= Constants::CHUNK_SIZE;
					p += pivot;
					(*chunks)[i][j]->init(p);
				}
			}
		}

		if (ed == LEFT || ed == RIGHT) {
			for (int i = 0; i < Constants::MAP_SIZE; ++i) {
				for (int j = 0; j < Constants::MAP_SIZE; ++j) {
					glm::i32vec3 p(ed == LEFT ? 1 : -Constants::MAP_SIZE, i, j);
					p *= Constants::CHUNK_SIZE;
					p += pivot;
					(*chunks)[i][j]->init(p);
				}
			}
		}

		if (ed == FORWARD || ed == BACKWARD) {
			for (int i = 0; i < Constants::MAP_SIZE; ++i) {
				for (int j = 0; j < Constants::MAP_SIZE; ++j) {
					glm::i32vec3 p(i, j, ed == FORWARD ? 1 : -Constants::MAP_SIZE);
					p *= Constants::CHUNK_SIZE;
					p += pivot;
					(*chunks)[i][j]->init(p);
				}
			}
		}

		tcb->push(chunks, ed);
		tcb->relink();
		Post(EEvent::PG_BuildVisibility, tcb, 0);
		Post(EEvent::PG_BuildMeshes2d, &*chunks, 0);
		delete chunks;
	}

	WorldBuilder::~WorldBuilder()
	{
	}

}
