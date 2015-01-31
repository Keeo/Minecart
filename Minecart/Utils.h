#pragma once
#include <thread>

#include "UtilsMemory.h"
#include "Constants.h"

namespace utils
{

	class Utils
	{
	public:
		inline static int worldMod(int x) {
			return ((x % Constants::MAP_SIZE) + Constants::MAP_SIZE) % Constants::MAP_SIZE;
		}

		static size_t getMemoryUsage()
		{
			return UtilsMemory::getCurrentRSS();
			//size_t peakSize = UtilsMemory::getPeakRSS();
		}

	};

}
