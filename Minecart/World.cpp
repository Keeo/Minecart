#include "stdafx.h"
#include "World.h"

namespace model
{

	World::World() : worldWatcher_(this), drawVector_(this)
	{
		chunks_.store(NULL);
		Register(EEvent::CameraChangedChunk, this, (model::Callback) & World::cameraChangedChunk);
	}

	void World::pushFromTop()
	{
		const glm::i32vec3* top = (*chunks_)[0][Constants::MAP_SIZE - 1][0]->getPosition();
		Chunk* c[Constants::MAP_SIZE][Constants::MAP_SIZE];

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				glm::i32vec3 p(i, 1, j);
				p *= Constants::CHUNK_SIZE;
				p += *top;
				c[i][j] = new Chunk(p);
				Post(EEvent::BuildMeshForChunk, c[i][j], 0);
			}
		}
		(*chunks_).pushTop(c);
		
	}

	void World::cameraChangedChunk(void* pdata)
	{
		glm::i32vec3& chunkPos = *reinterpret_cast<glm::i32vec3*>(pdata);
		const glm::i32vec3 center = (*(*chunks_)[Constants::MAP_SIZE / 2][Constants::MAP_SIZE / 2][Constants::MAP_SIZE / 2]->getPosition()) / Constants::CHUNK_SIZE;
		glm::i32vec3 diff = center - chunkPos;
	}

	void World::build(WorldBuilder* builder)
	{
		//chunks_ = builder->buildChunkMatrix();
		auto start = std::make_shared<glm::vec3>(0.0f);
		Post(EEvent::WatcherInit, &start, 0);
	}

	std::shared_ptr<std::vector<Chunk*>> World::getOrderedChunks()
	{
		return drawVector_.getChunkArray();
	}

	void World::setChunks(TripleChunkBuffer* tcb)
	{
		assert(chunks_.load() == NULL);
		chunks_.store(tcb);
	}

	TripleChunkBuffer* World::getChunks()
	{
		return chunks_.load();
	}

	void World::update(const GameTime& gameTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			//pushFromTop();
			EDirection ed = EDirection::UP;
			Post(EEvent::WatcherMove, &ed, 0);
		}
	}

	World::~World()
	{
	}

}