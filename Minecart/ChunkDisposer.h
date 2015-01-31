#pragma once

#include <atomic>

#include <boost/lockfree/queue.hpp>

#include "IEventMessagingSystem.h"
#include "Chunk.h"


namespace model
{

	class ChunkDisposer : IEventMessagingSystem
	{
		boost::lockfree::queue<Chunk*> chunks_;
		std::atomic<int> counter_ = 0;
		std::atomic<bool> disposeable_ = false;

	public:
		void setDisposable(bool disposable);
		ChunkDisposer();
		~ChunkDisposer();
		void flush();

		void dispose(Chunk* chunk);
	};

}
