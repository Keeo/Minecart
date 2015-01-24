#include "stdafx.h"
#include "WorldWatcher.h"

#include "World.h"

namespace model
{

	WorldWatcher::WorldWatcher(World* world) : world_(world)
	{
		std::thread worker(&model::WorldWatcher::run, this);
		worker.detach();

		Register(EEvent::ReorderChunkArray, this, (model::Callback)& WorldWatcher::reorderChunkArray);
		Register(EEvent::RebuildChunkArray, this, (model::Callback)& WorldWatcher::rebuildChunkArray);
	}

	void WorldWatcher::run()
	{
		while (true) {
			std::unique_lock<std::mutex> lk(m_);
			cv_.wait(lk, [&](){ return reorder || rebuild; });

			if (rebuild) {
				rebuild = false;
				std::shared_ptr<std::vector<Chunk*>> chunkArray = std::make_shared<std::vector<Chunk*>>();
				populateOrderingArray(chunkArray);
				swap(chunkArray);
			}

			if (reorder) {
				reorder = false;
				assert(distancePred_ != NULL);
				std::shared_ptr<std::vector<Chunk*>> chunkArray = std::make_shared<std::vector<Chunk*>>(*world_->getOrderedChunks());
				sortArray(chunkArray, distancePred_);
				swap(chunkArray);
			}

		}
	}

	void WorldWatcher::swap(std::shared_ptr<std::vector<Chunk*>> chunkArray)
	{
		world_->setOrderedChunks(chunkArray);
	}

	void WorldWatcher::populateOrderingArray(std::shared_ptr<std::vector<Chunk*>> chunkArray)
	{
		auto chunks = world_->getChunks();
		chunkArray->clear();

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					Chunk* c = (*chunks)[i][j][k];
					if (!c->readyRender) continue;
					chunkArray->push_back(c);
				}
			}
		}

	}

	void WorldWatcher::sortArray(std::shared_ptr<std::vector<Chunk*>> chunkArray, std::shared_ptr<DistancePred> distancePred)
	{
		DistancePred& dp = *distancePred;
		std::sort(chunkArray->begin(), chunkArray->end(), dp);
	}

	void WorldWatcher::reorderChunkArray(void* data)
	{
		distancePred_ = *(std::shared_ptr<model::DistancePred>*)data;
		reorder = true;
		cv_.notify_one();
	}

	void WorldWatcher::rebuildChunkArray(void* data)
	{
		rebuild = true;
		cv_.notify_one();
	}

	WorldWatcher::~WorldWatcher()
	{
	}

}
