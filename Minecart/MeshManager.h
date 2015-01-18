#pragma once

#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include <boost/lockfree/queue.hpp>

#include "MeshBuilder.h"
#include "IEventMessagingSystem.h"

namespace view {

	class MeshManager : model::IEventMessagingSystem
	{
		MeshBuilder meshBuilder_;
		
		boost::lockfree::queue<model::Chunk*> queue_;

		std::vector<model::Chunk*> served_;

		//std::thread worker_;
		std::condition_variable cv_;
		std::mutex m_;

		void run();
		void buildchunkAsync();

	public:
		

		void buildMeshForChunk(void* pchunk);
		void buildMeshBForChunk(void* pchunk);

		MeshManager();
		~MeshManager();
	};

}
