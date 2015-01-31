#pragma once

#include "IEventMessagingSystem.h"
#include "Chunk.h"

namespace model
{

	class ChunkFactory : IEventMessagingSystem
	{

	public:

		ChunkFactory();
		~ChunkFactory();
	};

}