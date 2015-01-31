#pragma once

#include <mutex>
#include <array>

#include <boost/lockfree/queue.hpp>
#include <boost/circular_buffer.hpp>
#include <glm/gtc/type_precision.hpp>

#include "Constants.h"
#include "Chunk.h"
#include "Utils.h"
#include "ChunkDisposer.h"

namespace model
{

	class TripleChunkBuffer : public boost::circular_buffer<boost::circular_buffer<boost::circular_buffer<Chunk*>>>
	{
		std::mutex m_;
	public:
		ChunkDisposer chunkDisposer;


		void lock();
		void unlock();

		void relink();

		void pushY(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>& chunk, EDirection dir);
		std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE> readY(EDirection dir);

		void deleteOld();

		TripleChunkBuffer(int size);
		~TripleChunkBuffer();
	};

}
