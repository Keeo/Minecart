#include "stdafx.h"
#include "World.h"

namespace model
{

	World::World() : chunkArray_(new std::vector<Chunk*>()), worldWatcher_(this)
	{
		chunkArray_->reserve(Constants::CHUNK_COUNT);

		Register(EEvent::CameraChangedChunk, this, (model::Callback) & World::cameraChangedChunk);
	}

	void World::cameraChangedChunk(void* pdata)
	{
		glm::i32vec3& chunkPos = *reinterpret_cast<glm::i32vec3*>(pdata);
		const glm::i32vec3 center = (*(*chunks_)[Constants::MAP_SIZE / 2][Constants::MAP_SIZE / 2][Constants::MAP_SIZE / 2]->getPosition()) / Constants::CHUNK_SIZE;
		glm::i32vec3 diff = center - chunkPos;

		for (int i = 0; i != abs(diff.y); ++i) {
			glm::i32vec3 pos = center;
			pos.y += Constants::MAP_SIZE + i;

			Chunk* c;
			if (diff.y > 0) {
				c = new Chunk(pos);
			}

			//chunks_[pos.x]
		}
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