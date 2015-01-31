#include "stdafx.h"
#include "MeshManager.h"

namespace view {

	MeshManager::MeshManager()
	{
		Register(EEvent::BuildMeshForChunk, this, (model::Callback)& MeshManager::buildMeshForChunk);
	}

	void MeshManager::buildMeshForChunk(model::Chunk* chunk)
	{
		meshBuilder_.buildMesh(chunk);
	}

	MeshManager::~MeshManager()
	{
	}

}
