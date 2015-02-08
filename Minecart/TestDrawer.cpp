#include "stdafx.h"
#include "TestDrawer.h"
#include "View.h"


namespace view
{

	void TestDrawer::draw(std::shared_ptr<model::Model> model, View* view)
	{
		view->setActive(true);
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
		//-------------//-------------//-------------//-------------//-------------//

		
		
		frameBuffer_->bind();
		glViewport(0, 0, Constants::RESOLUTION_X, Constants::RESOLUTION_Y);
		//glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		worldShader_.bind();
		draw(chunks, &worldShader_);
		frameBuffer_->unbind();

		std::vector<std::shared_ptr<opengl::Texture>>* tex = frameBuffer_->attachedTextures();
		opengl::Texture& tt = *tex->at(0);
		worldShader_.bindTexture("shadow" , tt, 2);

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
		frameBuffer_ = opengl::FrameBufferFactory::buildFramebuffer();
	}


	TestDrawer::~TestDrawer()
	{
	}

}
