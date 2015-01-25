#pragma once

#include <stdlib.h> 
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include "boost/circular_buffer.hpp"
#include <glm/gtc/type_precision.hpp>

#include "Constants.h"
#include "Chunk.h"
#include "GameTime.h"
#include "WorldBuilder.h"
#include "WorldWatcher.h"
#include "TripleChunkBuffer.h"
#include "DrawVector.h"

namespace model
{

	class World : IEventMessagingSystem
	{
		std::atomic<TripleChunkBuffer*> chunks_;
		
		DrawVector drawVector_;

		WorldWatcher worldWatcher_;

		void cameraChangedChunk(void* pdata);
		void pushFromTop();

	public:
		
		void build(WorldBuilder* builder);

		World();

		void update(const GameTime&);

		TripleChunkBuffer* getChunks();
		void setChunks(TripleChunkBuffer* tcb);

		std::shared_ptr<std::vector<Chunk*>> getOrderedChunks();

		~World();
	};

}
