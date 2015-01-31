#include "stdafx.h"
#include "ChunkDisposer.h"

namespace model
{

	ChunkDisposer::ChunkDisposer() : chunks_(100)
	{
		Register(EEvent::DisposeChunk, this, (Callback)& ChunkDisposer::dispose);
	}

	void ChunkDisposer::dispose(Chunk* chunk)
	{
		disposeable_ = false;
		counter_.store(counter_.load() + 1);
		
		chunks_.push(chunk);
	}

	void ChunkDisposer::setDisposable(bool disposable)
	{
		disposeable_.store(disposable);
	}

	void ChunkDisposer::flush()
	{
		if (chunks_.empty()) return;
		sf::Clock clock;
		int start = counter_;
		while (!chunks_.empty() && disposeable_ && (start-counter_) < 5) {
			Chunk* c;
			chunks_.pop(c);
			delete c;
			--counter_;
		}
		if (start - counter_ == 0) return;
		std::cout << "Disposing: " << (start - counter_) << " chunks in:" << std::setprecision(15) << clock.getElapsedTime().asSeconds() << "secs" << std::endl;
	}

	ChunkDisposer::~ChunkDisposer()
	{
	}

}
