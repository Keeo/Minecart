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
		

		void buildMeshForChunk(model::Chunk* chunk);

	public:

		MeshManager();
		~MeshManager();
	};

}
