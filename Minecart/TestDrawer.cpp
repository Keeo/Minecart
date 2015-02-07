#include "stdafx.h"
#include "TestDrawer.h"
#include "View.h"


namespace view
{

	void TestDrawer::draw(std::shared_ptr<model::Model> model, View* view)
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
		view->setActive(true);
		for (auto& c : chunks) {
			auto m = c->getMesh();
			if (!m->initDone) {
				m->init();
			}
			if (m->meshReady && !m->gpuReady) {
				m->moveToGpu();
			}
			if (m->reloadMesh) {
				m->moveToGpu();
				m->reloadMesh = false;
			}
		}
		view->setActive(false);
		texture.setActive(true);
		norDepShader_.bind();
		
		
		draw(chunks, &norDepShader_);
		texture.display();

		//texture.setActive(false);
		view->setActive(true);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		worldShader_.bind();
		draw(chunks, &worldShader_);
		

	}

	void TestDrawer::draw(std::vector<model::Chunk*>& chunks, BaseShader* shader)
	{
		for (auto& c : chunks) {
			auto m = c->getMesh();
			
			if (!m->gpuReady) continue;
			shader->loadModelMatrix(&c->model);
			m->draw();
		}
	}

	TestDrawer::TestDrawer()
	{
		bool ret = texture.create(Constants::RESOLUTION_X, Constants::RESOLUTION_Y, true);
		assert(ret);

		sf::Shader* s = worldShader_.getShader();
		s->setParameter("sampler", texture.getTexture());
	}


	TestDrawer::~TestDrawer()
	{
	}

}
