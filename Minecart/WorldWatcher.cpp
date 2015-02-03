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
		utils::ThreadUtils::setThreadPriority(utils::ThreadPriority::LOW);
		while (true) {
			std::unique_lock<std::mutex> lk(m_);
			cv_.wait(lk, [&](){ return initData_ != NULL || !moveData_.empty(); });

			if (initData_ != NULL) {
				TripleChunkBuffer* tcb = NULL;
				Post(InitSequence, &tcb, 0);
				world_->setChunks(tcb);
				Post(PG_BuildMeshesTCB, tcb, 0);
				initData_ = NULL;
			}

			EDirection ed;
			while (moveData_.pop(ed)) {
				TripleChunkBuffer* tcb = world_->getChunks();
				void* payload[2]{tcb, &ed};
				Post(EEvent::GenerateAndMoveSlice, &payload, 0);
				if (ed == UP) moveData_.push(RIGHT);
				if (ed == RIGHT) moveData_.push(FORWARD);
				if (ed == FORWARD) moveData_.push(DOWN);

				if (ed == DOWN) moveData_.push(LEFT);
				if (ed == LEFT) moveData_.push(BACKWARD);
				if (ed == BACKWARD) moveData_.push(UP);
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
