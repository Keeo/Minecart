#pragma once

#include <vector>

#include "boost/circular_buffer.hpp"
#include <glm/gtc/type_precision.hpp>

#include "Constants.h"
#include "Chunk.h"
#include "GameTime.h"
#include "WorldBuilder.h"

namespace model
{

	class World
	{
		typedef boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>> triple_circular_buffer;
		triple_circular_buffer* chunks_ = NULL;
		
		std::vector<Chunk*> chunkArray_;

		void injectDummyChunks();
		void connectChunks();

	public:
		
		void populateOrderingArray();
		void sortArray(DistancePred distancePred);

		void visit(WorldBuilder* builder);

		World();

		void update(const GameTime&);

		triple_circular_buffer* getChunks();
		std::vector<Chunk*>* getOrderedChunks();

		~World();
	};

}
