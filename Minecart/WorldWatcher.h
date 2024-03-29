#pragma once

#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include <boost/lockfree/queue.hpp>

#include "Constants.h"
#include "Chunk.h"
#include "IEventMessagingSystem.h"

namespace model
{
	class World;

	class WorldWatcher : IEventMessagingSystem
	{
		std::shared_ptr<model::DistancePred> distancePred_;
		std::condition_variable cv_;
		std::mutex m_;

		void run();

		std::shared_ptr<glm::vec3> initData_ = NULL;
		boost::lockfree::queue<EDirection> moveData_;

		void initEvent(void* data);
		void moveEvent(void* data);
		void changeEvent(void* data);

		World* world_;
		void moveErase(void* data);
	public:
		WorldWatcher(World* world);
		~WorldWatcher();
	};

}
