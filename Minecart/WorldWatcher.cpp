#include "stdafx.h"
#include "WorldWatcher.h"

#include "World.h"

namespace model
{

	WorldWatcher::WorldWatcher(World* world) : world_(world), moveData_(10)
	{
		std::thread worker(&model::WorldWatcher::run, this);
		worker.detach();

		Register(WatcherInit, this, (model::Callback) & WorldWatcher::initEvent);
		Register(WatcherMove, this, (model::Callback) & WorldWatcher::moveEvent);
		Register(WatcherChange, this, (model::Callback) & WorldWatcher::changeEvent);
	}

	void WorldWatcher::run()
	{
		while (true) {
			std::unique_lock<std::mutex> lk(m_);
			cv_.wait(lk, [&](){ return initData_ != NULL || !moveData_.empty(); });

			if (initData_ != NULL) {
				TripleChunkBuffer* tcb = NULL;
				Post(InitSequence, &tcb, 0);
				assert(tcb->size() == Constants::MAP_SIZE);
				world_->setChunks(tcb);

				std::vector<Chunk*> chunks;
				chunks.reserve(Constants::CHUNK_COUNT);
				for (auto& a : *tcb) {
					for (auto& b : a) {
						for (auto c : b) {
							chunks.push_back(c);
						}
					}
				}
				Post(EEvent::PG_BuildMeshes1d, &chunks, 0);

				initData_ = NULL;
			}

			while (!moveData_.empty()) {
				EDirection ed;
				moveData_.pop(ed);
				TripleChunkBuffer* tcb = world_->getChunks();
				const glm::i32vec3 top = *(*tcb)[0][Constants::MAP_SIZE - 1][0]->getPosition();

				std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE> c = tcb->readY(ed);
				for (int i = 0; i < Constants::MAP_SIZE; ++i) {
					for (int j = 0; j < Constants::MAP_SIZE; ++j) {
						glm::i32vec3 p(i, ed==UP ? 1 : -Constants::MAP_SIZE, j);
						p *= Constants::CHUNK_SIZE;
						p += top;
						c[i][j]->init(p);
					}
				}
				tcb->pushY(c, ed);
				tcb->relink();
				Post(EEvent::PG_BuildVisibility, tcb, 0);

				/*std::vector<Chunk*> chunks;
				chunks.reserve(Constants::MAP_SIZE * Constants::MAP_SIZE);
				for (int i = 0; i < Constants::MAP_SIZE; ++i) {
					for (int j = 0; j < Constants::MAP_SIZE; ++j) {
						chunks.push_back(c[i][j]);
					}
				}*/
				Post(EEvent::PG_BuildMeshes2d, &c, 0);
			}
		}
	}

	void WorldWatcher::initEvent(void* data)
	{
		initData_ = *(std::shared_ptr<glm::vec3>*)data;
		cv_.notify_one();
	}

	void WorldWatcher::moveEvent(void* data)
	{
		moveData_.push(*(EDirection*)data);
		cv_.notify_one();
	}

	void WorldWatcher::changeEvent(void* data)
	{

	}

	WorldWatcher::~WorldWatcher()
	{
	}

}
