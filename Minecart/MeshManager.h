#pragma once

#include "MeshBuilder.h"
#include "IEventMessagingSystem.h"


namespace view {

	class MeshManager : model::IEventMessagingSystem
	{
		MeshBuilder meshBuilder_;
		
	public:

		void buildMeshForChunk(void* pchunk);

		MeshManager();
		~MeshManager();
	};

}
