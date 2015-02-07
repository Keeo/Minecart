#include "stdafx.h"
#include "PoolGateway.h"

namespace model
{

	PoolGateway::PoolGateway() : tp_(3, Constants::MAP_SIZE + 50)
	{
		utils::ThreadUtils::setThreadPoolPriority(&tp_);

		Register(EEvent::PG_BuildMeshes1d, this, (model::Callback) & PoolGateway::buildMeshes1d);
		Register(EEvent::PG_BuildMeshes2d, this, (model::Callback) & PoolGateway::buildMeshes2d);
		Register(EEvent::PG_BuildMeshesTCB, this, (model::Callback) & PoolGateway::buildMeshesTCB);
		Register(EEvent::PG_BuildVisibility, this, (model::Callback) & PoolGateway::buildVisibility);
		Register(EEvent::PG_BuildCubes, this, (model::Callback) & PoolGateway::buildCubes);

		std::atomic<size_t>* s = &tp_.queueSize;
		std::thread t([s](){
			while (true) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) std::cout << "Queue size:" << *s << std::endl;
				std::chrono::milliseconds dura(100);
				std::this_thread::sleep_for(dura);
			}
		});
		t.detach();
	}

	void PoolGateway::buildMeshesTCB(model::TripleChunkBuffer* tcb)
	{
		std::future<void> results[Constants::CHUNK_COUNT];

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					Chunk* c = (*tcb)[i][j][k];
					results[i * Constants::MAP_SIZE * Constants::MAP_SIZE + j * Constants::MAP_SIZE + k] = tp_.push([c](int id)->void {
						c->Post(EEvent::BuildMeshForChunk, c, 0);
						c->Post(EEvent::RebuildDrawVector, 0, 0);
					});
				}
			}
		}

		wait(results, Constants::CHUNK_COUNT);
	}

	void PoolGateway::buildCubes(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* chunks)
	{
		std::future<void> results[Constants::MAP_SIZE * Constants::MAP_SIZE];

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				Chunk* c = (*chunks)[i][j];
				results[i * Constants::MAP_SIZE + j] = tp_.push([c](int id)->void {
					c->loadCubes();
				});
			}
		}

		wait(results, Constants::MAP_SIZE * Constants::MAP_SIZE);
	}

	void PoolGateway::buildMeshes1d(std::vector<Chunk*>* chunks)
	{
		std::future<void>* results = new std::future<void>[chunks->size()];

		for (int i = 0; i < chunks->size(); ++i) {
			Chunk* c = (*chunks)[i];
			results[i] = tp_.push([c](int id)->void{
				c->Post(EEvent::BuildMeshForChunk, c, 0);
				c->Post(EEvent::RebuildDrawVector, 0, 0);
			});
		}

		wait(results, chunks->size());

		delete[] results;
	}

	void PoolGateway::buildMeshes2d(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* chunks)
	{
		std::future<void> results[Constants::MAP_SIZE * Constants::MAP_SIZE];

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				Chunk* c = (*chunks)[i][j];
				results[i * Constants::MAP_SIZE + j] = tp_.push([c](int id)->void {
					c->Post(EEvent::BuildMeshForChunk, c, 0);
					c->Post(EEvent::RebuildDrawVector, 0, 0);
				});
			}
		}

		wait(results, Constants::MAP_SIZE * Constants::MAP_SIZE);
	}

	void PoolGateway::buildVisibility(TripleChunkBuffer* tcb)
	{
		std::future<void>* results = new std::future<void>[Constants::CHUNK_COUNT];

		int i = 0;
		for (auto& a : *tcb) {
			for (auto& b : a) {
				for (auto c : b) {
					results[i++] = tp_.push([c](int id)->void{ c->rebuildCubesVisibility(); });
				}
			}
		}

		wait(results, Constants::CHUNK_COUNT);

		delete[] results;
	}

	void PoolGateway::wait(std::future<void>* futures, size_t size)
	{
		for (int i = 0; i < size; ++i) {
			futures[i].get();
		}
	}

	PoolGateway::~PoolGateway()
	{
	}

}
