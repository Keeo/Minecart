#pragma once

#include <memory>

#include "EDirection.h"
#include "MeshStruct.h"
#include "Chunk.h"
#include "Cube.h"
#include "IEventMessagingSystem.h"

namespace view
{

	class MeshBuilder : model::IEventMessagingSystem
	{

		void buildSquare(MeshStruct& mesh, float x, float y, float z, EDirection d);
		void buildCube(MeshStruct& mesh, model::Cube& cube, int x, int y, int z);
	public:
		
		std::unique_ptr<MeshStruct> buildMesh(model::Chunk* chunk);
	};

}
