#include "stdafx.h"
#include "MeshBuilder.h"

namespace view
{
	
	std::unique_ptr<MeshStructB> MeshBuilder::buildMeshB(model::Chunk* chunk)
	{
		auto cubes = chunk->getCubes();
		auto mesh = std::make_unique<MeshStructB>();

		for (int i = 0; i < 32; ++i) {
			for (int j = 0; j < 32; ++j) {
				for (int k = 0; k < 32; ++k) {
					model::Cube& c = cubes[i][j][k];
					if (c.type == ECube::Air) continue;

					glm::vec3 pos = glm::vec3(i, j, k);
					if (c.isXPVisible()) {
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 1, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 0, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 1, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(1, 0, 0));
					}
					if (c.isYPVisible()) {
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 1, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 1, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 1, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 1, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 1, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 1, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 1, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 1, 0));
					}
					if (c.isZPVisible()) {
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 1, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 0, 1));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 1, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 0, 1));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 0, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 0, 1));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 0, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 0, 1));
					}
					if (c.isXNVisible()) {
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 1, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(-1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 1, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(-1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 0, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(-1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 0, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(-1, 0, 0));
					}
					if (c.isYNVisible()) {
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 0, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, -1, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 0, 1));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, -1, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, -1, 0));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 0, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, -1, 0));
					}
					if (c.isZNVisible()) {
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 1, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 0, -1));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(1, 0, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 0, -1));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 1, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 0, -1));
						mesh->g_vertex_buffer_data.push_back(pos + glm::vec3(0, 0, 0));
						mesh->g_vertex_buffer_data.push_back(glm::vec3(0, 0, -1));
					}

				}
			}
		}

		int quadcount = mesh->getQuadcount();
		mesh->g_index_buffer_data.resize(quadcount*6);
		for (int i = 0; i < quadcount; ++i) {
			mesh->g_index_buffer_data[6 * i + 0] = 4 * i + 0;
			mesh->g_index_buffer_data[6 * i + 1] = 4 * i + 1;
			mesh->g_index_buffer_data[6 * i + 2] = 4 * i + 2;
			mesh->g_index_buffer_data[6 * i + 3] = 4 * i + 2;
			mesh->g_index_buffer_data[6 * i + 4] = 4 * i + 1;
			mesh->g_index_buffer_data[6 * i + 5] = 4 * i + 3;
		}


		mesh->init();
		mesh->moveToGpu();
		mesh->model = glm::translate(*chunk->getPosition());

		return mesh;
	}

	std::unique_ptr<MeshStruct> MeshBuilder::buildMesh(model::Chunk* chunk)
	{
		auto cubes = chunk->getCubes();
		auto mesh = std::make_unique<MeshStruct>();

		for (int i = 0; i < 32; ++i) {
			for (int j = 0; j < 32; ++j) {
				for (int k = 0; k < 32; ++k) {
					buildCube(*mesh, cubes[i][j][k], i, j, k);
				}
			}
		}

		mesh->init();
		mesh->moveToGpu();
		mesh->model = glm::translate(*chunk->getPosition());

		return mesh;
	}

	void MeshBuilder::buildCube(MeshStruct& mesh, model::Cube& cube, int x, int y, int z)
	{
		if (cube.type == Air) return;

		if (cube.isYPVisible())
		{
			buildSquare(mesh, x, y, z, UP);
		}

		if (cube.isYNVisible())
		{
			buildSquare(mesh, x, y, z, DOWN);
		}

		if (cube.isXNVisible())
		{
			buildSquare(mesh, x, y, z, LEFT);
		}

		if (cube.isXPVisible())
		{
			buildSquare(mesh, x, y, z, RIGHT);
		}

		if (cube.isZNVisible())
		{
			buildSquare(mesh, x, y, z, FORWARD);
		}

		if (cube.isZPVisible())
		{
			buildSquare(mesh, x, y, z, BACKWARD);
		}
	}

	void MeshBuilder::buildSquare(MeshStruct& mesh, float x, float y, float z, EDirection d)
	{
		const float cm = 1.0f;

		switch (d)
		{
		case UP:
			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);


			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			break;

		case DOWN:
			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);


			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			break;

		case LEFT:
			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);


			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			break;

		case RIGHT:
			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);


			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			break;

		case FORWARD:
			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);


			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			break;

		case BACKWARD:
			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);


			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 0 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(0);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 1 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(1);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			mesh.g_vertex_buffer_data.push_back(cm * 0 + x);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + y);
			mesh.g_vertex_buffer_data.push_back(cm * 1 + z);

			mesh.g_vertex_buffer_data.push_back(0);
			mesh.g_vertex_buffer_data.push_back(1);
			mesh.pushNormal(d);

			break;
		}
	}


}
