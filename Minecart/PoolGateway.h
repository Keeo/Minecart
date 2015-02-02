#pragma once

#include <chrono>

#include "Chunk.h"
#include "ThreadPool.h"
#include "MeshBuilder.h"
#include "TripleChunkBuffer.h"
#include "ThreadUtils.h"

namespace model
{

	class PoolGateway : IEventMessagingSystem
	{
		utils::ThreadPool tp_;
		view::MeshBuilder meshBuilder_;

		void buildMeshes1d(std::vector<Chunk*>* chunks);
		void buildMeshes2d(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* chunks);
		void buildVisibility(TripleChunkBuffer* tcb);

		inline void wait(std::future<void>* futures, size_t size);
	public:

		PoolGateway();
		~PoolGateway();
	};

}
