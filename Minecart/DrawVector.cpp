#include "stdafx.h"
#include "DrawVector.h"

#include "World.h"

namespace model
{

	DrawVector::DrawVector(World* world) : world_(world), vector_(new std::vector<Chunk*>()), distancePred_(std::make_shared<DistancePred>(glm::vec3(0)))
	{
		reorder_ = false;
		rebuild_ = false;

		std::thread worker(&model::DrawVector::run, this);
		worker.detach();

		Register(EEvent::ReorderDrawVector, this, (model::Callback)& DrawVector::initReorder);
		Register(EEvent::RebuildDrawVector, this, (model::Callback)& DrawVector::initRebuild);
	}


	void DrawVector::run()
	{
		utils::ThreadUtils::setThreadPriority(utils::ThreadPriority::LOW);
		while (true) {
			std::unique_lock<std::mutex> lk(m_);
			cv_.wait(lk, [&](){ return reorder_ || rebuild_; });

			if (rebuild_) {
				rebuild_ = false;
				std::shared_ptr<std::vector<Chunk*>> chunkArray = std::make_shared<std::vector<Chunk*>>();
				populateOrderingArray(chunkArray);
				sortArray(chunkArray, distancePred_);
				swap(chunkArray);
				world_->getChunks()->chunkDisposer.setDisposable(true);
			}

			if (reorder_) {
				reorder_ = false;
				assert(distancePred_ != NULL);
				if (vector_->size() == 0) continue;
				std::shared_ptr<std::vector<Chunk*>> chunkArray = std::make_shared<std::vector<Chunk*>>(*vector_);
				sortArray(chunkArray, distancePred_);
				swap(chunkArray);
			}

		}
	}

	void DrawVector::swap(std::shared_ptr<std::vector<Chunk*>> vector)
	{
		vector_ = vector;
	}

	void DrawVector::populateOrderingArray(std::shared_ptr<std::vector<Chunk*>> chunkArray)
	{
		TripleChunkBuffer* chunks = world_->getChunks();
		assert(chunks != NULL);
		chunkArray->clear();

		chunks->lock();
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					Chunk* c = (*chunks)[i][j][k];
					if (!c->readyRender) continue;
					assert(c->getMesh() != NULL);
					chunkArray->push_back(c);
				}
			}
		}
		chunks->unlock();

	}

	void DrawVector::sortArray(std::shared_ptr<std::vector<Chunk*>> chunkArray, std::shared_ptr<DistancePred> distancePred)
	{
		DistancePred dp = *distancePred;
		std::sort(chunkArray->begin(), chunkArray->end(), dp);

		assert([](std::shared_ptr<std::vector<Chunk*>> ca, DistancePred* dp)->bool{
			if ((*ca).size() == 0) return true;
			for (int i = 0; i < ca->size() - 1; ++i) {
				float first = glm::distance(dp->pos, *ca->at(i)->getCenter());
				float second = glm::distance(dp->pos, *ca->at(i + 1)->getCenter());

				if (first > second) {
					if (ca->at(i)->readyRender && ca->at(i + 1)->readyRender) {
						return false;
					}
				}
			}
			return true;
		}(chunkArray, &dp));
	}


	void DrawVector::initRebuild(void* data)
	{
		rebuild_ = true;
		cv_.notify_one();
	}

	void DrawVector::initReorder(void* data)
	{
		distancePred_ = *(std::shared_ptr<model::DistancePred>*)data;
		reorder_ = true;
		cv_.notify_one();
	}

	std::shared_ptr<std::vector<Chunk*>> DrawVector::getChunkArray()
	{
		return vector_;
	}

	DrawVector::~DrawVector()
	{
	}

}
