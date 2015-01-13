#include "stdafx.h"
#include "MeshManager.h"

namespace view {

	MeshManager::MeshManager()
	{
		Register(EEvent::BuildMeshForChunk, this, (model::Callback)& MeshManager::buildMeshForChunk);
	}

	void MeshManager::buildMeshForChunk(void* pchunk)
	{
		model::Chunk* chunk = (model::Chunk*)pchunk;
		auto mesh = meshBuilder_.buildMesh(chunk);
		chunk->setMesh(std::move(mesh));
	}

	MeshManager::~MeshManager()
	{
	}

}
