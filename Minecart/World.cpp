#include "stdafx.h"
#include "World.h"

namespace model {

	World::World()
	{
	}


	void World::visit(WorldBuilder* builder)
	{
		chunks_ = builder->buildChunkMatrix();
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