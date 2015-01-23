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

	public:

		TripleChunkBuffer* buildChunkMatrix();

		WorldBuilder();
		~WorldBuilder();
	};

}
