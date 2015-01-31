#pragma once

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

	class DrawVector : IEventMessagingSystem
	{
		std::shared_ptr<model::DistancePred> distancePred_;
		std::condition_variable cv_;
		std::mutex m_;

		void run();
		
		void initReorder(void* data);
		void initRebuild(void* data);

		std::atomic<bool> reorder_;
		std::atomic<bool> rebuild_;
		std::atomic<bool> load_;

		void swap(std::shared_ptr<std::vector<Chunk*>> chunkArray);
		void populateOrderingArray(std::shared_ptr<std::vector<Chunk*>> chunkArray);
		void sortArray(std::shared_ptr<std::vector<Chunk*>> chunkArray, std::shared_ptr<DistancePred> distancePred);

		std::shared_ptr<std::vector<Chunk*>> vector_;

		boost::lockfree::queue<Chunk*> toLoad_;
		void toLoad(Chunk* chunk);

		World* world_;

	public:

		std::shared_ptr<std::vector<Chunk*>> getChunkArray();

		DrawVector(World* world);
		~DrawVector();
	};

}
