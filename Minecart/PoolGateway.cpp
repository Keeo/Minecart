#include "stdafx.h"
#include "PoolGateway.h"

namespace model
{

	PoolGateway::PoolGateway() : tp_(4)
	{
		Register(EEvent::PG_BuildMeshes, this, (model::Callback) & PoolGateway::buildMeshes);
		Register(EEvent::PG_BuildVisibility, this, (model::Callback) & PoolGateway::buildVisibility);
	}

	void PoolGateway::buildMeshes(std::vector<Chunk*>* chunks)
	{
		std::future<void>* results = new std::future<void>[chunks->size()];

		for (int i = 0; i < chunks->size(); ++i) {
			results[i] = tp_.push([](int id, Chunk* c)->void{ c->Post(EEvent::BuildMeshForChunk, c, 0); c->Post(EEvent::RebuildDrawVector, 0, 0); }, (*chunks)[i]);
		}

		wait(results, chunks->size());

		delete[] results;
	}

	void PoolGateway::buildVisibility(TripleChunkBuffer* tcb)
	{
		std::future<void>* results = new std::future<void>[Constants::CHUNK_COUNT];

		int i = 0;
		for (auto& a : *tcb) {
			for (auto& b : a) {
				for (auto c : b) {
					results[i++] = tp_.push([](int id, Chunk* c)->void{ c->rebuildCubesVisibility(); }, c);
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
