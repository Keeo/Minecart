#include "stdafx.h"
#include "World.h"

namespace model
{

	World::World() : chunkArray_(new std::vector<Chunk*>()), worldWatcher_(this)
	{
		chunkArray_->reserve(Constants::CHUNK_COUNT);
	}

	void World::visit(WorldBuilder* builder)
	{
		chunks_ = builder->buildChunkMatrix();
	}


	void World::setOrderedChunks(std::shared_ptr<std::vector<Chunk*>> chunkArray)
	{
		chunkArray_ = chunkArray;
	}

	std::shared_ptr<std::vector<Chunk*>> World::getOrderedChunks()
	{
		return chunkArray_;
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