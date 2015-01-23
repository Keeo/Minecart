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

namespace model
{

	class World : IEventMessagingSystem
	{
		TripleChunkBuffer* chunks_ = NULL;
		
		std::shared_ptr<std::vector<Chunk*>> chunkArray_;

		//void injectDummyChunks();
		//void connectChunks();
		WorldWatcher worldWatcher_;

		void cameraChangedChunk(void* pdata);
		void pushFromTop();

	public:
		
		void visit(WorldBuilder* builder);

		World();

		void update(const GameTime&);

		TripleChunkBuffer* getChunks();
		
		std::shared_ptr<std::vector<Chunk*>> getOrderedChunks();
		void setOrderedChunks(std::shared_ptr<std::vector<Chunk*>> chunkArray);

		~World();
	};

}
