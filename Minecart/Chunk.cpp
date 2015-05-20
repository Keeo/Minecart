#include "stdafx.h"
#include "Chunk.h"

namespace model {

	Chunk::Chunk(glm::i32vec3 position) : position_(position), center_(position + Constants::CHUNK_SIZE / 2)
	{
		loadCubes();
		model = glm::translate(static_cast<glm::vec3>(position_));
	}

	bool Chunk::putCube(glm::i32vec3 pos, ECube cube)
	{
		glm::i32vec3 local = utils::Utils::globalToLocal(pos);
		if (cubes_[local.x][local.y][local.z].type == cube) return false;
		cubes_[local.x][local.y][local.z].type = cube;
		rebuildOneCubeChangeVisibility(local);
		return true;
	}

	ECube Chunk::getCube(const glm::i32vec3& pos)
	{
		glm::i32vec3 local = utils::Utils::globalToLocal(pos);
		return cubes_[local.x][local.y][local.z].type;
	}

	void Chunk::rebuildOneCubeChangeVisibility(glm::i32vec3 local)
	{
		assert(local.x >= 0 && local.x < Constants::CHUNK_SIZE);
		assert(local.y >= 0 && local.y < Constants::CHUNK_SIZE);
		assert(local.z >= 0 && local.z < Constants::CHUNK_SIZE);

		std::vector<Chunk*> chunksToRebuild;
		const int EDGE = Constants::CHUNK_SIZE - 1;
		chunksToRebuild.push_back(this);
		if (cubes_[local.x][local.y][local.z].type != ECube::Air) {
			rebuildCubeVisibility(local.x, local.y, local.z);
		}
		else{
			if (local.x == 0) {
				w->rebuildCubeVisibility(EDGE, local.y, local.z);
				chunksToRebuild.push_back(w);
			}
			else {
				rebuildCubeVisibility(local.x - 1, local.y, local.z);
			}

			if (local.x == EDGE) {
				e->rebuildCubeVisibility(0, local.y, local.z);
				chunksToRebuild.push_back(e);
			}
			else {
				rebuildCubeVisibility(local.x + 1, local.y, local.z);
			}

			if (local.y == 0) {
				d->rebuildCubeVisibility(local.x, EDGE, local.z);
				chunksToRebuild.push_back(d);
			}
			else {
				rebuildCubeVisibility(local.x, local.y - 1, local.z);
			}

			if (local.y == EDGE) {
				u->rebuildCubeVisibility(local.x, 0, local.z);
				chunksToRebuild.push_back(u);
			}
			else {
				rebuildCubeVisibility(local.x, local.y + 1, local.z);
			}

			if (local.z == 0) {
				n->rebuildCubeVisibility(local.x, local.y, EDGE);
				chunksToRebuild.push_back(n);
			}
			else {
				rebuildCubeVisibility(local.x, local.y, local.z - 1);
			}

			if (local.z == EDGE) {
				s->rebuildCubeVisibility(local.x, local.y, 0);
				chunksToRebuild.push_back(s);
			}
			else {
				rebuildCubeVisibility(local.x, local.y, local.z + 1);
			}
			sf::Clock c;
			bool type;
			if (chunksToRebuild.size() == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Home)) {
				Post(EEvent::BuildMeshForChunk, chunksToRebuild[0], 0);
				type = false;
			}
			else {
				type = true;
				Post(EEvent::PG_BuildMeshes1d, &chunksToRebuild, 0);
			}
			std::cout << (type ? "PG" : "1T") << " was waiting for chunk rebuild: " << std::setprecision(15) << c.getElapsedTime().asSeconds() << std::endl;
		}
	}

	void Chunk::init(glm::i32vec3 position)
	{
		Drawable::reset();
		position_ = position;
		center_ = position + Constants::CHUNK_SIZE / 2;
		model = glm::translate(static_cast<glm::vec3>(position_));
	}

	bool Chunk::assertLinks()
	{
		return u->d == this && d->u == this &&
			w->e == this && e->w == this &&
			n->s == this && s->n == this;
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

	void Chunk::setNeighbors(Chunk* up, Chunk* down, Chunk* east, Chunk* west, Chunk* north, Chunk* south)
	{
		u = up;
		d = down;

		e = east;
		w = west;

		n = north;
		s = south;
	}

	void Chunk::loadCubes()
	{
		utils::SimplexNoise sn;
		for (int i = 0; i < Constants::CHUNK_SIZE; ++i) {
			for (int j = 0; j < Constants::CHUNK_SIZE; ++j) {
				for (int k = 0; k < Constants::CHUNK_SIZE; ++k) {
					const glm::i32vec3 pos = position_ + glm::i32vec3(i, j, k);
					float noise = sn.octave_noise_3d(1.0f, 0.05f, 0.5f, static_cast<float>(pos.x) / 128.0f, static_cast<float>(pos.y) / 128.0f, static_cast<float>(pos.z) / 128.0f);
					//cubes_[i][j][k].type = noise < 0.7f ? ECube::Dirt : ECube::Air;
					
					cubes_[i][j][k].type = (rand() % 64) < Constants::CUBE_TRESHOLD ? ECube::Dirt : ECube::Air;
					//cubes_[i][j][k].type = i+j+k < 16 ? ECube::Dirt : ECube::Air;
					//cubes_[i][j][k].type = j + position_.y < Constants::CHUNK_SIZE+5 ? ECube::Dirt : ECube::Air;

					/*cubes_[i][j][k].type = ECube::Air;
					if (i == 0 || j == 0 || k == 0 || i == Constants::CHUNK_SIZE || j == Constants::CHUNK_SIZE || k == Constants::CHUNK_SIZE) {
					cubes_[i][j][k].type = ECube::Dirt;
					}*/
				}
			}
		}
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