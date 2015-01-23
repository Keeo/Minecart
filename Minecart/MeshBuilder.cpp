#include "stdafx.h"
#include "MeshBuilder.h"

namespace view
{
	
	std::unique_ptr<MeshStruct> MeshBuilder::buildMesh(model::Chunk* chunk)
	{
		auto cubes = chunk->getCubes();
		auto mesh = std::make_unique<MeshStruct>();

		for (int i = 0; i < Constants::CHUNK_SIZE; ++i) {
			for (int j = 0; j < Constants::CHUNK_SIZE; ++j) {
				for (int k = 0; k < Constants::CHUNK_SIZE; ++k) {
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

		size_t quadcount = mesh->getQuadcount();
		mesh->g_index_buffer_data.resize(quadcount*6);
		for (int i = 0; i < quadcount; ++i) {
			mesh->g_index_buffer_data[6 * i + 0] = 4 * i + 0;
			mesh->g_index_buffer_data[6 * i + 1] = 4 * i + 1;
			mesh->g_index_buffer_data[6 * i + 2] = 4 * i + 2;
			mesh->g_index_buffer_data[6 * i + 3] = 4 * i + 2;
			mesh->g_index_buffer_data[6 * i + 4] = 4 * i + 1;
			mesh->g_index_buffer_data[6 * i + 5] = 4 * i + 3;
		}

		/*mesh->init();
		mesh->moveToGpu();
		mesh->makeVAO();*/

		return mesh;
	}

}
