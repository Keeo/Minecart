#include "stdafx.h"
#include "MeshBuilder.h"

namespace view
{
	
	void MeshBuilder::buildMesh(model::Chunk* chunk)
	{
		auto cubes = chunk->getCubes();

		auto mesh = chunk->getMesh() == NULL ? std::make_shared<MeshStruct>() : chunk->getMesh();
		
		std::lock_guard<std::mutex> lg(mesh->meshBuilding);

		auto& vertex_buffer = *mesh->g_vertex_buffer_data;
		auto& index_buffer = *mesh->g_index_buffer_data;

		vertex_buffer.clear();
		index_buffer.clear();

		for (int i = 0; i < Constants::CHUNK_SIZE; ++i) {
			for (int j = 0; j < Constants::CHUNK_SIZE; ++j) {
				for (int k = 0; k < Constants::CHUNK_SIZE; ++k) {
					model::Cube& c = cubes[i][j][k];
					if (c.type == ECube::Air) continue;
					// 00 xx yy zz
					//  100 = 16
					// -100 = 48
					//  010 = 4
					// 0-10 = 12
					//  001 = 1
					// 00-1 = 3

					const glm::u8vec4 pos(i, j, k, 0);
					if (c.isXPVisible()) {
						vertex_buffer.push_back(pos + glm::u8vec4(1, 1, 1, 16));
						vertex_buffer.push_back(getTextureCoord(0, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(1, 0, 1, 16));
						vertex_buffer.push_back(getTextureCoord(2, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(1, 1, 0, 16));
						vertex_buffer.push_back(getTextureCoord(1, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(1, 0, 0, 16));
						vertex_buffer.push_back(getTextureCoord(3, c.type));
					}
					if (c.isYPVisible()) {
						vertex_buffer.push_back(pos + glm::u8vec4(1, 1, 1, 4));
						vertex_buffer.push_back(getTextureCoord(0, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(1, 1, 0, 4));
						vertex_buffer.push_back(getTextureCoord(1, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 1, 1, 4));
						vertex_buffer.push_back(getTextureCoord(2, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 1, 0, 4));
						vertex_buffer.push_back(getTextureCoord(3, c.type));
					}
					if (c.isZPVisible()) {
						vertex_buffer.push_back(pos + glm::u8vec4(1, 1, 1, 1));
						vertex_buffer.push_back(getTextureCoord(0, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 1, 1, 1));
						vertex_buffer.push_back(getTextureCoord(1, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(1, 0, 1, 1));
						vertex_buffer.push_back(getTextureCoord(2, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 0, 1, 1));
						vertex_buffer.push_back(getTextureCoord(3, c.type));
					}
					if (c.isXNVisible()) {
						vertex_buffer.push_back(pos + glm::u8vec4(0, 1, 1, 48));
						vertex_buffer.push_back(getTextureCoord(0, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 1, 0, 48));
						vertex_buffer.push_back(getTextureCoord(1, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 0, 1, 48));
						vertex_buffer.push_back(getTextureCoord(2, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 0, 0, 48));
						vertex_buffer.push_back(getTextureCoord(3, c.type));
					}
					if (c.isYNVisible()) {
						vertex_buffer.push_back(pos + glm::u8vec4(1, 0, 1, 12));
						vertex_buffer.push_back(getTextureCoord(0, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 0, 1, 12));
						vertex_buffer.push_back(getTextureCoord(1, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(1, 0, 0, 12));
						vertex_buffer.push_back(getTextureCoord(2, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 0, 0, 12));
						vertex_buffer.push_back(getTextureCoord(3, c.type));
					}
					if (c.isZNVisible()) {
						vertex_buffer.push_back(pos + glm::u8vec4(1, 1, 0, 3));
						vertex_buffer.push_back(getTextureCoord(1, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(1, 0, 0, 3));
						vertex_buffer.push_back(getTextureCoord(3, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 1, 0, 3));
						vertex_buffer.push_back(getTextureCoord(0, c.type));
						vertex_buffer.push_back(pos + glm::u8vec4(0, 0, 0, 3));
						vertex_buffer.push_back(getTextureCoord(2, c.type));
					}

				}
			}
		}

		mesh->quadcount = vertex_buffer.size() / 8;

		index_buffer.resize(mesh->quadcount * 6);
		for (int i = 0; i < mesh->quadcount; ++i) {
			index_buffer[6 * i + 0] = 4 * i + 0;
			index_buffer[6 * i + 1] = 4 * i + 1;
			index_buffer[6 * i + 2] = 4 * i + 2;
			index_buffer[6 * i + 3] = 4 * i + 2;
			index_buffer[6 * i + 4] = 4 * i + 1;
			index_buffer[6 * i + 5] = 4 * i + 3;
		}

		chunk->setMesh(mesh);

		if (mesh->meshReady) {
			mesh->reloadMesh = true;
		}
		else{
			mesh->meshReady = true;
		}

	}


	glm::i8vec4 MeshBuilder::getTextureCoord(int pos, ECube type)
	{
		const int per = 8;
		const int length = 256;
		glm::i8vec4 vector;
		switch (pos) {
		case 0:
			return glm::i8vec4(1, 1, 0, 0);
		case 1:
			return glm::i8vec4(0, 1, 0, 0);
		case 2:
			return glm::i8vec4(1, 0, 0, 0);
		case 3:
			return glm::i8vec4(0, 0, 0, 0);
		default:
			assert(false);
		}
		return glm::i8vec4(0);
	}
}
