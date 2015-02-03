#pragma once

#include "boost/circular_buffer.hpp"
#include <glm/gtc/type_precision.hpp>

#include "Utils.h"
#include "Chunk.h"
#include "IEventMessagingSystem.h"
#include "TripleChunkBuffer.h"

namespace model
{

	class WorldBuilder : IEventMessagingSystem
	{
		void initSequence(void* data);
		void generateSlice(void** data);
	public:

		void relink(TripleChunkBuffer* chunks);
		void fillChunks(TripleChunkBuffer* chunks);
		void rebuildVisibility(TripleChunkBuffer* chunks);

		TripleChunkBuffer* buildChunkMatrix();

		WorldBuilder();
		~WorldBuilder();
	};

}
