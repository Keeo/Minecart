#pragma once

#include <memory>
#include <mutex>

#include "EDirection.h"
#include "MeshStruct.h"
#include "Chunk.h"
#include "Cube.h"
#include "IEventMessagingSystem.h"
#include "ThreadPool.h"

namespace view
{

	class MeshBuilder : model::IEventMessagingSystem
	{

	public:
		void buildMesh(model::Chunk* chunk);
	};

}
