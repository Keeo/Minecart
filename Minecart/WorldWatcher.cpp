#include "stdafx.h"
#include "WorldWatcher.h"

#include "World.h"

namespace model
{

	WorldWatcher::WorldWatcher(World* world) : world_(world)
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
			cv_.wait(lk, [&](){ return initData_ != NULL; });

			if (initData_ != NULL) {
				TripleChunkBuffer* tcb = NULL;
				Post(InitSequence, &tcb, 0);
				assert(tcb->size() == Constants::MAP_SIZE);
				world_->setChunks(tcb);

				for (auto& a : *tcb) {
					for (auto& b : a) {
						for (auto c : b) {
							Post(EEvent::BuildMeshForChunk, c, 0);
						}
					}
				}

				initData_ = NULL;
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

	}

	void WorldWatcher::changeEvent(void* data)
	{

	}

	WorldWatcher::~WorldWatcher()
	{
	}

}
