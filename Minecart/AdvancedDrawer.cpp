#include "stdafx.h"
#include "AdvancedDrawer.h"

namespace view
{
	void AdvancedDrawer::condDraw(std::shared_ptr<model::Model> model)
	{
		CameraData cameraData;
		Post(EEvent::FetchCameraData, &cameraData, 0);
			
		auto world = model->getWorld();

		static int frames = 0;
		if (frames++ > 30) {
			frames = 0;
			std::shared_ptr<model::DistancePred> dp = std::make_shared<model::DistancePred>(*cameraData.position);
			Post(EEvent::ReorderDrawVector, &dp, 0);
		}
		auto smartChunks = world->getOrderedChunks();
		std::vector<model::Chunk*>& chunks = *smartChunks;
		for (auto a : chunks) {
			if (a->getMesh()->indexBufferID == -1) {
				auto m = a->getMesh();
				m->init();
				m->moveToGpu();
				m->makeVAO();
				//m->newOrder();
			}
		}


		int i = 0;
		bool occlusion_cull = !sf::Keyboard::isKeyPressed(sf::Keyboard::O);
		bool cpucull = !sf::Keyboard::isKeyPressed(sf::Keyboard::I);

		float maxdist = Constants::CHUNK_SIZE;
		float add = Constants::CHUNK_SIZE * 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			maxdist /= 2; 
			add /= 2;
		}
		int culled = 0;
		while (i != chunks.size()) {
			int j = i;
			if (occlusion_cull) {
				// start occlusion queries and render for the current slice
				glDisable(GL_CULL_FACE);

				// we don't want the queries to actually render something
				glDepthMask(GL_FALSE);
				glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

				simpleShader_.bind();

				for (; j < chunks.size() && glm::distance(*(chunks[j]->getCenter()), *cameraData.position) < maxdist; ++j) {
					// frustum culling
					if (cpucull && isCullable(cameraData, chunks[j])) {
						culled++;
						continue;
					}

					// begin occlusion query
					glBeginQuery(GL_ANY_SAMPLES_PASSED, query_[j]);

					// draw bounding box
					simpleShader_.loadModelMatrix(&chunks[j]->model);
					box_.draw();
					
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
				if (cpucull && isCullable(cameraData, chunks[j])) continue;

				

				// begin conditional render
				if (occlusion_cull)
					glBeginConditionalRender(query_[j], GL_QUERY_BY_REGION_WAIT);

				worldShader_.loadModelMatrix(&chunks[j]->model);
				chunks[j]->getMesh()->draw();

				// end conditional render
				if (occlusion_cull)
					glEndConditionalRender();
			}
			i = j;
			maxdist += add;
		}

		//glDeleteQueries(query.size(), query.data());

		int rendered = 0;
		for (auto& a : query_) {
			GLint pa = 0;
			glGetQueryObjectiv(a, GL_QUERY_RESULT, &pa);
			rendered += pa;
		}

		//std::cout << "Total:"<<chunks.size()<< " skipped:" << (chunks.size() - rendered) << " rendered:" << rendered << " culled:" << culled << " memusage:" << Utils::getMemoryUsage() << std::endl;
	}


	bool AdvancedDrawer::isCullable(CameraData& cd, model::Chunk* chunk)
	{
		glm::vec4 projected = *cd.projection * *cd.view * glm::vec4(*chunk->getCenter(), 1);
		return glm::distance(*(chunk->getCenter()), *cd.position) > Constants::CHUNK_SIZE &&
			(std::max(std::abs(projected.x), std::abs(projected.y)) > projected.w + Constants::CHUNK_SIZE);
	}

	AdvancedDrawer::AdvancedDrawer()
	{
		query_.resize(Constants::CHUNK_COUNT);
		glGenQueries(static_cast<GLsizei>(query_.size()), query_.data());
	}


	AdvancedDrawer::~AdvancedDrawer()
	{
		glDeleteQueries(static_cast<GLsizei>(query_.size()), query_.data());
	}

}
