#pragma once

#include "boost/circular_buffer.hpp"
#include <glm/gtc/type_precision.hpp>

#include "Constants.h"
#include "Chunk.h"

namespace model
{

	class TripleChunkBuffer : public boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>>
	{
	public:

		void pushTop(Chunk* (&chunk)[Constants::MAP_SIZE][Constants::MAP_SIZE]);

		TripleChunkBuffer(int size);
		~TripleChunkBuffer();
	};

}
