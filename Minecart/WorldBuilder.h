#pragma once

#include "boost/circular_buffer.hpp"
#include <glm/gtc/type_precision.hpp>

#include "Utils.h"
#include "Chunk.h"

namespace model
{

	class WorldBuilder
	{

	public:

		boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>>* buildChunkMatrix();

		WorldBuilder();
		~WorldBuilder();
	};

}
