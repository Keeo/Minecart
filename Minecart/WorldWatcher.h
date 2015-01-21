#pragma once

#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

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

		void populateOrderingArray(std::shared_ptr<std::vector<Chunk*>> chunkArray);
		void sortArray(std::shared_ptr<std::vector<Chunk*>> chunkArray, std::shared_ptr<DistancePred> distancePred);
		
		void swap(std::vector<Chunk*>* chunkArray);
		void swap(std::shared_ptr<std::vector<Chunk*>> chunkArray);

		void reorderChunkArray(void* data);
		void rebuildChunkArray(void* data);


		bool reorder = false;
		bool rebuild = false;

		World* world_;

	public:
		WorldWatcher(World* world);
		~WorldWatcher();
	};

}
