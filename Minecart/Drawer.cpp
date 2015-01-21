#include "stdafx.h"
#include "Drawer.h"

namespace view
{

	void Drawer::draw(std::shared_ptr<model::Model> model) {
		auto chunks = *(model->getWorld()->getChunks());

		//worldShader_.bind();
		//draw(chunks[0][0][0]);
		//draw(chunks[0][0][1]);
		//draw(chunks[0][0][2]);
		for (int i = 0; i < chunks.size(); ++i) {
			for (int j = 0; j < chunks[i].size(); ++j) {
				for (int k = 0; k < chunks[j].size(); ++k) {
					drawBoundingBoxFor(chunks[i][j][k]);
					//draw(chunks[i][j][k]);
				}
			}
		}
		//worldShader_.unbind();
	}

	void Drawer::drawBoundingBoxFor(model::Chunk* chunk)
	{
		simpleShader_.bind();
		simpleShader_.loadModelMatrix(&chunk->model);
		box_.draw();
		simpleShader_.unbind();
	}

	void Drawer::draw(model::Chunk* chunk)
	{
		std::shared_ptr<MeshStruct> mesh = chunk->getMesh();
		if (mesh == NULL) {
			Post(EEvent::BuildMeshForChunk, chunk, 0);
			mesh = chunk->getMesh();
			assert(mesh != NULL);
		}

		worldShader_.bind();
		mesh->draw();
		worldShader_.unbind();
	}

	Drawer::Drawer()
	{
	}


	Drawer::~Drawer()
	{
	}

}
