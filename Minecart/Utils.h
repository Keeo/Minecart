#pragma once
#include <thread>

#include "Memory.h"
#include "Constants.h"

namespace utils
{

	class Utils
	{
	public:

		 template <typename T>
		 inline static int sgn(T val) {
			return (0 < val) - (val < 0);
		}

		inline static glm::i32vec3 sgn(const glm::vec3& g) {
			return glm::i32vec3(Utils::sgn(g.x), Utils::sgn(g.y), Utils::sgn(g.z));
		}

		inline static glm::i32vec3 globalToChunk(const glm::i32vec3& global)
		{
			return global / Constants::CHUNK_SIZE;
		}

		inline static glm::i32vec3 globalToLocal(const glm::i32vec3& global)
		{
			return glm::i32vec3(chunkMod(global.x), chunkMod(global.y), chunkMod(global.z));
		}

		inline static int chunkMod(int x)
		{
			return ((x % Constants::CHUNK_SIZE) + Constants::CHUNK_SIZE) % Constants::CHUNK_SIZE;
		}

		inline static int worldMod(int x)
		{
			return ((x % Constants::MAP_SIZE) + Constants::MAP_SIZE) % Constants::MAP_SIZE;
		}

		inline static bool isInside(const glm::i32vec3& chunkPos)
		{
			return chunkPos.x >= 0 && chunkPos.y >= 0 && chunkPos.z >= 0 &&
				chunkPos.x < Constants::MAP_SIZE && chunkPos.y < Constants::MAP_SIZE && chunkPos.z < Constants::MAP_SIZE;
		}

		static size_t getMemoryUsage()
		{
			return Memory::getCurrentRSS();
		}

	};

}
