#include "stdafx.h"
#include "AdvancedDrawer.h"

namespace view
{

	void AdvancedDrawer::draw(std::shared_ptr<model::Model> model) {
		auto world = model->getWorld();
		world->populateOrderingArray();
		world->sortArray(model::DistancePred(glm::vec3(0,0,0)));

		auto chunks = world->getOrderedChunks();

		for (int i = 0; i < chunks->size(); ++i) {
			drawBoundingBoxFor((*chunks)[i]);
		}
	}

	void AdvancedDrawer::drawBoundingBoxFor(model::Chunk* chunk)
	{
		simpleShader_.bind();
		simpleShader_.loadModelMatrix(&chunk->model);
		box_.getMesh()->bind();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			glDrawElements(GL_LINES, 6 * 6, GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
		}
		box_.getMesh()->unbind();
		simpleShader_.unbind();
	}

	void AdvancedDrawer::draw(model::Chunk* chunk)
	{
		std::shared_ptr<MeshStruct> mesh = chunk->getMesh();
		if (mesh == NULL) {
			Post(EEvent::BuildMeshForChunk, chunk, 0);
			mesh = chunk->getMesh();
			assert(mesh != NULL);
		}


		worldShader_.bind();
		mesh->bind();

		worldShader_.loadModelMatrix(&chunk->model);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			glDrawElements(GL_LINES, 6 * mesh->getQuadcount(), GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawElements(GL_TRIANGLES, 6 * mesh->getQuadcount(), GL_UNSIGNED_INT, 0);
		}

		mesh->unbind();
		worldShader_.unbind();
	}

	AdvancedDrawer::AdvancedDrawer()
	{
	}


	AdvancedDrawer::~AdvancedDrawer()
	{
	}

}
