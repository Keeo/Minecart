#include "stdafx.h"
#include "MeshManager.h"

namespace view {

	MeshManager::MeshManager() : queue_(10)
	{
		std::thread worker(&view::MeshManager::run, this);
		worker.detach();

		Register(EEvent::BuildMeshForChunk, this, (model::Callback)& MeshManager::buildMeshForChunk);
	}

	void MeshManager::run()
	{
		while (true) {
			std::unique_lock<std::mutex> lk(m_);
			cv_.wait(lk, [&](){ return !queue_.empty(); });

			while (!queue_.empty()) {
				buildchunkAsync();
				Post(EEvent::RebuildDrawVector, NULL, 0);
			}
			
			std::cout << "Mesh builder work done." << std::endl;
		}
	}

	void MeshManager::buildMeshForChunk(void* pchunk)
	{
		queue_.push((model::Chunk*)pchunk);
		cv_.notify_one();
	}

	void MeshManager::buildchunkAsync()
	{
		model::Chunk* chunk;
		bool ret = queue_.pop(chunk);
		assert(ret);

		auto mesh = meshBuilder_.buildMesh(chunk);
		chunk->setMesh(std::move(mesh));
	}

	MeshManager::~MeshManager()
	{
	}

}
