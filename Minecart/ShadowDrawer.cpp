#include "stdafx.h"
#include "TestDrawer.h"
#include "View.h"


namespace view
{

	void ShadowDrawer::draw(std::shared_ptr<model::Model> model, View* view)
	{
		//-------------//-------------//-------------//-------------//-------------//
		// this semgnet will setup world and its elements
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
		static bool cull = true; ///< toggle for GL_FRONT cull in Depth pass
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			cull = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			cull = false;
		}

		//-- Depth pass
		glm::vec3 lightPos;
		Post(EEvent::FetchLightData, &lightPos, 0); /// fetch light possition
		if (cull) glCullFace(GL_FRONT);
		shadowBuffer_->bind(); /// binds shadow buffer
		shadowBuffer_->setPassShadow(); /// sets shadow pass
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /// clears colors and depth
		depthShader_.bind(); /// bind depth shader
		draw(chunks, &depthShader_); /// draws world
		if (cull) glCullFace(GL_BACK);
		glClearColor(0.f, 0.f, 0.f, 0.f); /// no idea why its here
		opengl::Texture& depthTextureStart = *shadowBuffer_->attachedTextures()->at(0); /// gets ping texture from framebuffer
		opengl::Texture& depthTextureEnd = *shadowBuffer_->attachedTextures()->at(1); /// gets pong texture from framebuffer

		//-- Blur pass
		glDisable(GL_DEPTH_TEST); /// will render quads, no depth check required
		
		int amount = log2(Constants::RESOLUTION_X); /// calculate amount of loops required
		for (int i = 0; i < amount; ++i) {
			satXShader_.bind(i); /// binds satX shader
			satXShader_.bindTexture("image", depthTextureStart, 1); /// bind ping texture
			GLuint attachments[1] = { GL_COLOR_ATTACHMENT1 }; /// will render to pong texture
			glDrawBuffers(1, attachments);
			glClear(GL_COLOR_BUFFER_BIT); /// clears color
			sc_.draw(true); /// draw quad
			
			++i; /// next loop
			satXShader_.bind(i); /// binds satX shader
			satXShader_.bindTexture("image", depthTextureEnd, 0); /// bind pong texture
			GLuint attachments2[1] = { GL_COLOR_ATTACHMENT0 }; /// will render to ping texture
			glDrawBuffers(1, attachments2);
			glClear(GL_COLOR_BUFFER_BIT); /// clears color
			sc_.draw(true); /// draw quad
		}

		/// same as for X sat shader but this time for Y shader
		amount = log2(Constants::RESOLUTION_Y);
		for (int i = 0; i < amount; ++i) {
			satYShader_.bind(i);
			satYShader_.bindTexture("image", depthTextureStart, 1);
			GLuint attachments[1] = { GL_COLOR_ATTACHMENT1 };
			glDrawBuffers(1, attachments);
			glClear(GL_COLOR_BUFFER_BIT);
			sc_.draw(true);

			++i;
			satYShader_.bind(i);
			satYShader_.bindTexture("image", depthTextureEnd, 0);
			GLuint attachments2[1] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, attachments2);
			glClear(GL_COLOR_BUFFER_BIT);
			sc_.draw(true);
		}

		shadowBuffer_->unbind(); /// unbinds shadow buffer
		glEnable(GL_DEPTH_TEST); /// enable depth text

		//-- Render pass
		lightShader_.bind(); /// bind light shader
		glViewport(0, 0, Constants::RESOLUTION_X, Constants::RESOLUTION_Y); /// fix viewport
		lightShader_.bindTexture("shadow", *shadowBuffer_->attachedTextures()->at(0)); /// use ping texture
		draw(chunks, &lightShader_); /// draw world
		lightShader_.unbind(); /// unbind light shader
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
