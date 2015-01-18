#include "stdafx.h"
#include "AdvancedDrawer.h"

namespace view
{
	void AdvancedDrawer::condDraw(std::shared_ptr<model::Model> model)
	{
		CameraData cameraData;
		Post(EEvent::FetchCameraData, &cameraData, 0);
			
		auto world = model->getWorld();
		world->populateOrderingArray();
		world->sortArray(model::DistancePred(*cameraData.position));
		std::vector<model::Chunk*>& chunks = *world->getOrderedChunks();
		
		int i = 0;
		bool occlusion_cull = !sf::Keyboard::isKeyPressed(sf::Keyboard::O);
		
		float maxdist = Constants::CHUNK_SIZE;
		std::vector<GLuint> query(chunks.size());
		glGenQueries(chunks.size(), query.data());

		while (i != chunks.size()) {
			size_t j = i;
			if (occlusion_cull) {
				// start occlusion queries and render for the current slice
				glDisable(GL_CULL_FACE);

				// we don't want the queries to actually render something
				glDepthMask(GL_FALSE);
				glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

				simpleShader_.bind();

				for (; j < chunks.size() && glm::distance(*(chunks[j]->getCenter()), *cameraData.position) < maxdist; ++j) {
					// frustum culling
					if (isCullable(cameraData, chunks[j])) continue;

					// begin occlusion query
					glBeginQuery(GL_ANY_SAMPLES_PASSED, query[j]);

					// draw bounding box
					simpleShader_.loadModelMatrix(&chunks[j]->model);
					box_.getMesh()->bind();
					glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
					box_.getMesh()->unbind();

					// end occlusion query
					glEndQuery(GL_ANY_SAMPLES_PASSED);
				}
				j = i;
			}

			// render the current slice
			glEnable(GL_CULL_FACE);

			// turn rendering back on
			glDepthMask(GL_TRUE);
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			worldShader_.bind();
			for (; j < chunks.size() && glm::distance(*(chunks[j]->getCenter()), *cameraData.position) < maxdist; ++j) {
				// frustum culling
				if (isCullable(cameraData, chunks[j])) continue;

				// begin conditional render
				if (occlusion_cull)
					glBeginConditionalRender(query[j], GL_QUERY_BY_REGION_WAIT);

				auto mesh = chunks[j]->getMesh();
				mesh->bind();

				worldShader_.loadModelMatrix(&chunks[j]->model);
				
				GLuint rendertype = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ? GL_LINES : GL_TRIANGLES;
				glDrawElements(rendertype, 6 * mesh->getQuadcount(), GL_UNSIGNED_INT, 0);
				
				mesh->unbind();

				// end conditional render
				if (occlusion_cull)
					glEndConditionalRender();
			}
			i = j;
			maxdist += 2 * Constants::CHUNK_SIZE;
		}

		/*int rendered = 0;
		for (auto& a : query) {
			GLint pa = 0;
			glGetQueryObjectiv(a, GL_QUERY_RESULT, &pa);
			rendered += pa;
		}
		std::cout << (chunks.size() - rendered) << std::endl;*/
	}


	bool AdvancedDrawer::isCullable(CameraData& cd, model::Chunk* chunk)
	{
		glm::vec4 projected = *cd.projection * *cd.view * glm::vec4(*chunk->getCenter(), 1);
		return glm::distance(*(chunk->getCenter()), *cd.position) > Constants::CHUNK_SIZE &&
			(std::max(std::abs(projected.x), std::abs(projected.y)) > projected.w + Constants::CHUNK_SIZE);
	}

	AdvancedDrawer::AdvancedDrawer()
	{
	}


	AdvancedDrawer::~AdvancedDrawer()
	{
	}

}
