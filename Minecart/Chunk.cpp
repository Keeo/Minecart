#include "stdafx.h"
#include "Chunk.h"

namespace model {

	Chunk::Chunk(glm::i32vec3 position) : position_(position), center_(position + Constants::CHUNK_SIZE / 2)
	{
		for (int i = 0; i < Constants::CHUNK_SIZE; ++i) {
			for (int j = 0; j < Constants::CHUNK_SIZE; ++j) {
				for (int k = 0; k < Constants::CHUNK_SIZE; ++k) {
					cubes_[i][j][k].type = (rand() % (Constants::CHUNK_SIZE * 4)) < 8 ? ECube::Dirt : ECube::Air;
					//cubes_[i][j][k].type = i+j+k < 16 ? ECube::Dirt : ECube::Air;

					/*cubes_[i][j][k].type = ECube::Dirt;
					if (i == 0 || j == 0 || k == 0 || i == Constants::CHUNK_SIZE || j == Constants::CHUNK_SIZE || k == Constants::CHUNK_SIZE) {
					cubes_[i][j][k].type = ECube::Air;
					}*/
				}
			}
		}

		rebuildCubesVisibilityCore();

		model = glm::translate(position_);
	}


	void Chunk::assertLinks()
	{
		assert(u->d == this);
		assert(d->u == this);

		assert(s->e == this);
		assert(e->s == this);

		assert(n->w == this);
		assert(w->n == this);
	}

	Chunk::~Chunk()
	{
	}

	void Chunk::rebuildCubeVisibility(int i, int j, int k)
	{
		const int edge = Constants::CHUNK_SIZE - 1;

		Cube& c = cubes_[i][j][k];
		c.visible = 0;

		if (c.type == ECube::Air) return;

		if (i == edge) {
			if (e->cubes_[0][j][k].type == ECube::Air) {
				c.visible |= 1 << 5;
				assert(c.isXPVisible());
			}
		}
		else {
			if (cubes_[i + 1][j][k].type == ECube::Air) {
				c.visible |= 1 << 5;
				assert(c.isXPVisible());
			}
		}

		if (i == 0) {
			if (w->cubes_[edge][j][k].type == ECube::Air) {
				c.visible |= 1 << 4;
				assert(c.isXNVisible());
			}
		}
		else {
			if (cubes_[i - 1][j][k].type == ECube::Air) {
				c.visible |= 1 << 4;
				assert(c.isXNVisible());
			}
		}


		if (j == edge) {
			if (u->cubes_[i][0][k].type == ECube::Air) {
				c.visible |= 1 << 3;
				assert(c.isYPVisible());
			}
		}
		else {
			if (cubes_[i][j + 1][k].type == ECube::Air) {
				c.visible |= 1 << 3;
				assert(c.isYPVisible());
			}
		}

		if (j == 0) {
			if (d->cubes_[i][edge][k].type == ECube::Air) {
				c.visible |= 1 << 2;
				assert(c.isYNVisible());
			}
		}
		else {
			if (cubes_[i][j - 1][k].type == ECube::Air) {
				c.visible |= 1 << 2;
				assert(c.isYNVisible());
			}
		}


		if (k == edge) {
			if (n->cubes_[i][j][0].type == ECube::Air) {
				c.visible |= 1 << 1;
				assert(c.isZPVisible());
			}
		}
		else {
			if (cubes_[i][j][k + 1].type == ECube::Air) {
				c.visible |= 1 << 1;
				assert(c.isZPVisible());
			}
		}

		if (k == 0) {
			if (s->cubes_[i][j][edge].type == ECube::Air) {
				c.visible |= 1 << 0;
				assert(c.isZNVisible());
			}
		}
		else {
			if (cubes_[i][j][k - 1].type == ECube::Air) {
				c.visible |= 1 << 0;
				assert(c.isZNVisible());
			}
		}
	}

	void Chunk::rebuildCubesVisibility()
	{
		const int edge = Constants::CHUNK_SIZE - 1;

		for (int i = 0; i < Constants::CHUNK_SIZE; ++i) {
			for (int j = 0; j < Constants::CHUNK_SIZE; ++j) {
				for (int k = 0; k < Constants::CHUNK_SIZE; ++k) {
					rebuildCubeVisibility(i, j, k);
				}
			}
		}
	}

	void Chunk::rebuildCubesVisibilityCore()
	{
		const int start = 1;
		const int end = Constants::CHUNK_SIZE - 1;

		for (int i = start; i < end; ++i) {
			for (int j = start; j < end; ++j) {
				for (int k = start; k < end; ++k) {
					Cube& c = cubes_[i][j][k];
					c.visible = 0;
					if (c.type == ECube::Air) continue;

					if (cubes_[i + 1][j][k].type == ECube::Air) {
						c.visible |= 1 << 5;
						assert(c.isXPVisible());
					}
					if (cubes_[i - 1][j][k].type == ECube::Air) {
						c.visible |= 1 << 4;
						assert(c.isXNVisible());
					}

					if (cubes_[i][j + 1][k].type == ECube::Air) {
						c.visible |= 1 << 3;
						assert(c.isYPVisible());
					}
					if (cubes_[i][j - 1][k].type == ECube::Air) {
						c.visible |= 1 << 2;
						assert(c.isYNVisible());
					}

					if (cubes_[i][j][k + 1].type == ECube::Air) {
						c.visible |= 1 << 1;
						assert(c.isZPVisible());
					}
					if (cubes_[i][j][k - 1].type == ECube::Air) {
						c.visible |= 1 << 0;
						assert(c.isZNVisible());
					}
				}
			}
		}
	}

	void Chunk::rebuildCubesVisibilityEdge(EDirection dir)
	{
		const int edge = Constants::CHUNK_SIZE - 1;

		int xstart = dir == EDirection::RIGHT ? edge : 0;
		int xend = dir == EDirection::LEFT ? 1 : Constants::CHUNK_SIZE;

		int ystart = dir == EDirection::UP ? edge : 0;
		int yend = dir == EDirection::DOWN ? 1 : Constants::CHUNK_SIZE;

		int zstart = dir == EDirection::FORWARD ? edge : 0;
		int zend = dir == EDirection::BACKWARD ? 1 : Constants::CHUNK_SIZE;


		for (int i = xstart; i < xend; ++i) {
			for (int j = ystart; j < yend; ++j) {
				for (int k = zstart; k < zend; ++k) {
					rebuildCubeVisibility(i, j, k);
				}
			}
		}
	}

	void Chunk::setNeighbors(Chunk* up, Chunk* down, Chunk* north, Chunk* west, Chunk* east, Chunk* south)
	{
		u = up;
		d = down;
		n = north;
		w = west;
		e = east;
		s = south;
	}

	Cube(&Chunk::getCubes())[Constants::CHUNK_SIZE][Constants::CHUNK_SIZE][Constants::CHUNK_SIZE]
	{
		return cubes_;
	}

	const glm::i32vec3* Chunk::getPosition() const
	{
		return &position_;
	}

	const glm::vec3* Chunk::getCenter() const
	{
		return &center_;
	}
}