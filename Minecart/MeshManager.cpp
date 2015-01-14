#include "stdafx.h"
#include "MeshManager.h"

namespace view {

	MeshManager::MeshManager()
	{
		Register(EEvent::BuildMeshForChunk, this, (model::Callback)& MeshManager::buildMeshForChunk);
		Register(EEvent::BuildMeshBForChunk, this, (model::Callback)& MeshManager::buildMeshBForChunk);
	}

	void MeshManager::buildMeshForChunk(void* pchunk)
	{
		model::Chunk* chunk = (model::Chunk*)pchunk;
		auto mesh = meshBuilder_.buildMesh(chunk);
		chunk->setMesh(std::move(mesh));
	}

	void MeshManager::buildMeshBForChunk(void* pchunk)
	{
		model::Chunk* chunk = (model::Chunk*)pchunk;
		auto mesh = meshBuilder_.buildMeshB(chunk);
		chunk->setMeshB(std::move(mesh));
	}

	MeshManager::~MeshManager()
	{
	}

}
