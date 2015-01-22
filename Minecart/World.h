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

namespace model
{

	class World : IEventMessagingSystem
	{
		typedef boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>> triple_circular_buffer;
		triple_circular_buffer* chunks_ = NULL;
		
		std::shared_ptr<std::vector<Chunk*>> chunkArray_;

		//void injectDummyChunks();
		//void connectChunks();
		WorldWatcher worldWatcher_;

		void cameraChangedChunk(void* pdata);

	public:
		
		void visit(WorldBuilder* builder);

		World();

		void update(const GameTime&);

		triple_circular_buffer* getChunks();
		
		std::shared_ptr<std::vector<Chunk*>> getOrderedChunks();
		void setOrderedChunks(std::shared_ptr<std::vector<Chunk*>> chunkArray);

		~World();
	};

}
