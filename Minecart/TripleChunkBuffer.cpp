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

	void TripleChunkBuffer::pushTop(Chunk* (&chunk)[Constants::MAP_SIZE][Constants::MAP_SIZE])
	{
		boost::circular_buffer<Chunk*> slices[Constants::MAP_SIZE];
		for (int i = 0; i < Constants::MAP_SIZE; ++i) slices[i].set_capacity(Constants::MAP_SIZE);

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				slices[i].push_back(chunk[i][j]);
			}
			assert(slices[i].size() == Constants::MAP_SIZE);
		}

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			(*this)[i].push_back(slices[i]);
		}
	}

	TripleChunkBuffer::~TripleChunkBuffer()
	{
	}

}
