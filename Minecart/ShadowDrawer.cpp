#include "stdafx.h"
#include "TestDrawer.h"
#include "View.h"


namespace view
{

	void ShadowDrawer::draw(std::shared_ptr<model::Model> model, View* view)
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

		glm::vec3 lightPos;
		Post(EEvent::FetchLightData, &lightPos, 0);

		shadowBuffer_->bind();
		shadowBuffer_->setPassShadow();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		depthShader_.bind();
		draw(chunks, &depthShader_);
		shadowBuffer_->unbind();

		
		lightShader_.bind();
		glViewport(0, 0, Constants::RESOLUTION_X, Constants::RESOLUTION_Y);
		lightShader_.bindTexture("shadow", *shadowBuffer_->attachedTextures()->at(0));
		draw(chunks, &lightShader_);
		lightShader_.unbind();



		/*frameBuffer_->bind();
		frameBuffer_->setPassDisplay();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		worldShader_.bind();
		draw(chunks, &worldShader_);
		frameBuffer_->unbind();

		std::map<GLuint, std::shared_ptr<opengl::Texture>>* tex = frameBuffer_->attachedTextures();
		opengl::Texture& t2 = *tex->at(1); // nordep
		opengl::Texture& tt = *tex->at(0); // color

		opengl::Texture& ssao = *frameSmallBuffer_->attachedTextures()->at(0);
		opengl::Texture& pong = *frameSmallBuffer_->attachedTextures()->at(1);

		frameSmallBuffer_->bind();
		frameSmallBuffer_->setPassSSAO();
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);

		ssaoShader_.bind();
		ssaoShader_.bindTexture("normalMap", t2, 1);
		sc_.draw(true);

		for (int i = 0; i > 5; ++i){
			blurXShader_.bind();
			blurXShader_.bindTexture("image", ssao, 0);
			GLuint attachments[1] = { GL_COLOR_ATTACHMENT1 };
			glDrawBuffers(1, attachments);
			glClear(GL_COLOR_BUFFER_BIT);
			sc_.draw(true);

			blurYShader_.bind();
			blurYShader_.bindTexture("image", pong, 0);
			GLuint attachments2[1] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, attachments2);
			glClear(GL_COLOR_BUFFER_BIT);
			sc_.draw(true);
		}

		frameSmallBuffer_->unbind();
		texShader_.bind();
		glViewport(0, 0, Constants::RESOLUTION_X, Constants::RESOLUTION_Y);
		texShader_.bindTexture("image", tt);
		texShader_.bindTexture("ssao", ssao, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		sc_.draw(true);
		glEnable(GL_DEPTH_TEST);*/
		glEnable(GL_DEPTH_TEST);
	}

	void ShadowDrawer::draw(std::vector<model::Chunk*>& chunks, BaseShader* shader)
	{
		for (auto& c : chunks) {
			auto m = c->getMesh();

			if (!m->gpuReady) continue;
			shader->loadModelMatrix(&c->model);
			m->draw();
		}
	}

	ShadowDrawer::ShadowDrawer()
	{
		//frameBuffer_ = opengl::FrameBufferFactory::buildFramebuffer();
		//frameSmallBuffer_ = opengl::FrameBufferFactory::buildSmallFramebuffer();
		shadowBuffer_ = opengl::FrameBufferFactory::buildShadowFramebuffer();
	}


	ShadowDrawer::~ShadowDrawer()
	{
	}

}
