#pragma once

#include <memory>


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
		std::future<bool> buildMeshParaler(model::Chunk* chunk);
		std::shared_ptr<MeshStruct> buildMesh(model::Chunk* chunk);
	};

}
