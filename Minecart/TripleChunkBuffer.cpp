#include "stdafx.h"
#include "TripleChunkBuffer.h"

namespace model
{

	TripleChunkBuffer::TripleChunkBuffer(int size) : circular_buffer(size)
	{
		for (int i = 0; i < size; ++i) {
			boost::circular_buffer<boost::circular_buffer<Chunk*>> temp(size);
			for (int j = 0; j < size; ++j) {
				temp.push_back(boost::circular_buffer<Chunk*>(size));
			}
			push_back(temp);
		}
	}

	std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE> TripleChunkBuffer::readY(EDirection dir)
	{
		std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE> chunks;
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			int j = 0;
			if (dir == UP) {
				for (auto a : (*this)[i].front()) {
					chunks[i][j++] = a;
				}
			}
			else  {
				for (auto a : (*this)[i].back()) {
					chunks[i][j++] = a;
				}
			}
		}
		return chunks;
	}

	void TripleChunkBuffer::pushY(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>& chunk, EDirection dir)
	{
		assert(dir == EDirection::UP || dir == EDirection::DOWN);
		boost::circular_buffer<Chunk*> slices[Constants::MAP_SIZE];
		for (int i = 0; i < Constants::MAP_SIZE; ++i) slices[i].set_capacity(Constants::MAP_SIZE);

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				slices[i].push_back(chunk[i][j]);
			}
			assert(slices[i].size() == Constants::MAP_SIZE);
		}

		std::lock_guard<std::mutex> lg(m_);
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			
			if (dir == UP) {
				(*this)[i].push_back(slices[i]);
			}
			else {
				(*this)[i].push_front(slices[i]);
			}
		}
	}

	void TripleChunkBuffer::relink()
	{
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				for (int k = 0; k < Constants::MAP_SIZE; ++k) {
					Chunk& c = *(*this)[i][j][k];
					using namespace utils;
					c.setNeighbors(
						(*this)[i][Utils::worldMod(j + 1)][k],
						(*this)[i][Utils::worldMod(j - 1)][k],

						(*this)[Utils::worldMod(i + 1)][j][k],
						(*this)[Utils::worldMod(i - 1)][j][k],

						(*this)[i][j][Utils::worldMod(k + 1)],
						(*this)[i][j][Utils::worldMod(k - 1)]
						);
				}
			}
		}

		assert([](TripleChunkBuffer* tcb)->bool{
			for (int i = 0; i < Constants::MAP_SIZE; ++i) {
				for (int j = 0; j < Constants::MAP_SIZE; ++j) {
					for (int k = 0; k < Constants::MAP_SIZE; ++k) {
						bool ret = (*tcb)[i][j][k]->assertLinks();
						if (ret == false) return false;
					}
				}
			}
			return true;
		}(this));
	}

	TripleChunkBuffer::~TripleChunkBuffer()
	{
	}

	void TripleChunkBuffer::lock()
	{
		m_.lock();
	}

	void TripleChunkBuffer::unlock()
	{
		m_.unlock();
	}

}
