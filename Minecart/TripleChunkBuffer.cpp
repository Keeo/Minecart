#include "stdafx.h"
#include "TripleChunkBuffer.h"

namespace model
{

	TripleChunkBuffer::TripleChunkBuffer(int size) : circular_buffer(size), cubeFinder(this)
	{
		for (int i = 0; i < size; ++i) {
			boost::circular_buffer<boost::circular_buffer<Chunk*>> temp(size);
			for (int j = 0; j < size; ++j) {
				temp.push_back(boost::circular_buffer<Chunk*>(size));
			}
			push_back(temp);
		}
	}

	ECube TripleChunkBuffer::getCube(const glm::i32vec3& pos)
	{
		Chunk* chunk = getChunk(pos);
		if (chunk == NULL) {
			return ECube::Air;
		}
		else {
			return chunk->getCube(pos);
		}
	}

	Chunk* TripleChunkBuffer::getChunk(const glm::i32vec3& pos)
	{
		using namespace utils;
		glm::i32vec3 posCoord = Utils::globalToChunk(pos);
		glm::i32vec3 myCoord = Utils::globalToChunk(*(*this)[0][0][0]->getPosition());

		glm::i32vec3 realCoord = posCoord - myCoord;
		if (!Utils::isInside(realCoord)) return NULL;

		return (*this)[realCoord.x][realCoord.y][realCoord.z];
	}

	bool TripleChunkBuffer::putCube(glm::i32vec3 pos, ECube cube)
	{
		Chunk* chunk = getChunk(pos);
		if (chunk == NULL) {
			return false;
		}
		else {
			return chunk->putCube(pos, cube);
		}
	}

	std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* TripleChunkBuffer::read(EDirection dir)
	{
		if (dir == LEFT || dir == RIGHT) return readX(dir);
		if (dir == UP || dir == DOWN) return readY(dir);
		if (dir == FORWARD || dir == BACKWARD) return readZ(dir);
		assert(false);
		return NULL;
	}

	void TripleChunkBuffer::push(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* chunk, EDirection dir)
	{
		if (dir == LEFT || dir == RIGHT) {
			pushX(chunk, dir);
			return;
		}
		if (dir == UP || dir == DOWN) {
			pushY(chunk, dir);
			return;
		}
		if (dir == FORWARD || dir == BACKWARD) {
			pushZ(chunk, dir);
			return;
		}
		assert(false);
	}

	std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* TripleChunkBuffer::readY(EDirection dir)
	{
		auto chunks = new std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>();
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			int j = 0;
			if (dir == UP) {
				for (auto a : (*this)[i].front()) {
					(*chunks)[i][j++] = a;
				}
			}
			else  {
				for (auto a : (*this)[i].back()) {
					(*chunks)[i][j++] = a;
				}
			}
		}
		return chunks;
	}

	void TripleChunkBuffer::pushY(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* chunk, EDirection dir)
	{
		assert(dir == EDirection::UP || dir == EDirection::DOWN);
		boost::circular_buffer<Chunk*> slices[Constants::MAP_SIZE];
		for (int i = 0; i < Constants::MAP_SIZE; ++i) slices[i].set_capacity(Constants::MAP_SIZE);

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				slices[i].push_back((*chunk)[i][j]);
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

	std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* TripleChunkBuffer::readX(EDirection dir)
	{
		assert(dir == EDirection::LEFT || dir == EDirection::RIGHT);
		auto chunks = new std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>();
		auto jump = dir == LEFT ? (*this).front() : (*this).back();

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			int j = 0;
			for (auto a : jump[i]) {
				(*chunks)[i][j++] = a;
			}
		}
		return chunks;
	}

	void TripleChunkBuffer::pushX(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* chunk, EDirection dir)
	{
		assert(dir == EDirection::LEFT || dir == EDirection::RIGHT);

		boost::circular_buffer<boost::circular_buffer<Chunk*>> temp(Constants::MAP_SIZE);
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			boost::circular_buffer<Chunk*> slice(Constants::MAP_SIZE);
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				slice.push_back((*chunk)[i][j]);
			}
			temp.push_back(slice);
		}

		std::lock_guard<std::mutex> lg(m_);
		if (dir == LEFT) {
			(*this).push_back(temp);
		}
		else {
			(*this).push_front(temp);
		}

	}

	std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* TripleChunkBuffer::readZ(EDirection dir)
	{
		assert(dir == EDirection::FORWARD || dir == EDirection::BACKWARD);
		auto chunks = new std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>();

		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				(*chunks)[i][j] = dir == FORWARD ? (*this)[i][j].front() : (*this)[i][j].back();
			}
		}
		return chunks;
	}

	void TripleChunkBuffer::pushZ(std::array<std::array<Chunk*, Constants::MAP_SIZE>, Constants::MAP_SIZE>* chunk, EDirection dir)
	{
		assert(dir == EDirection::FORWARD || dir == EDirection::BACKWARD);

		std::lock_guard<std::mutex> lg(m_);
		for (int i = 0; i < Constants::MAP_SIZE; ++i) {
			for (int j = 0; j < Constants::MAP_SIZE; ++j) {
				if (dir == FORWARD) {
					(*this)[i][j].push_back((*chunk)[i][j]);
				}
				else {
					(*this)[i][j].push_front((*chunk)[i][j]);
				}
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
		std::cout << "re";
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
