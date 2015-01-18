#include "stdafx.h"
#include "World.h"

namespace model {

	World::World() : chunkArray_(Constants::MAP_SIZE*Constants::MAP_SIZE*Constants::MAP_SIZE)
	{
	}

	void World::populateOrderingArray()
	{
		chunkArray_.clear();
		
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					Chunk* c = (*chunks_)[i][j][k];
					if (!c->readyRender) continue;
					if (c->getMesh()->indexBufferID == -1) {
						auto m = c->getMesh();
						m->init();
						m->moveToGpu();
						m->makeVAO();
					}
					chunkArray_.push_back(c);
				}
			}
		}
		
	}

	void World::sortArray(DistancePred distancePred)
	{
		std::sort(chunkArray_.begin(), chunkArray_.end(), distancePred);
	}

	void World::visit(WorldBuilder* builder)
	{
		chunks_ = builder->buildChunkMatrix();
	}

	std::vector<Chunk*>* World::getOrderedChunks()
	{
		return &chunkArray_;
	}

	boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>>* World::getChunks()
	{
		return chunks_;
	}

	void World::update(const GameTime& gameTime)
	{

	}

	World::~World()
	{
	}

}