#include "stdafx.h"
#include "World.h"

namespace model
{

	World::World() : worldWatcher_(this), drawVector_(this)
	{
		chunks_.store(NULL);
		Register(EEvent::CameraChangedChunk, this, (model::Callback) & World::cameraChangedChunk);
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
		static bool lastU = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) || sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton1)) {
			if (!lastU) {
				EDirection ed = EDirection::UP;
				Post(EEvent::WatcherMove, &ed, 0);
				lastU = true;
			}
		}
		else {
			lastU = false;
		}

		static bool lastD = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2)) {
			if (!lastD) {
				EDirection ed = EDirection::DOWN;
				Post(EEvent::WatcherMove, &ed, 0);
				lastD = true;
			}
		}
		else {
			lastD = false;
		}


		static bool lastL = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
			if (!lastL) {
				EDirection ed = EDirection::LEFT;
				Post(EEvent::WatcherMove, &ed, 0);
				lastL = true;
			}
		}
		else {
			lastL = false;
		}

		static bool lastR = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			if (!lastR) {
				EDirection ed = EDirection::RIGHT;
				Post(EEvent::WatcherMove, &ed, 0);
				lastR = true;
			}
		}
		else {
			lastR = false;
		}
	}

	World::~World()
	{
	}

}