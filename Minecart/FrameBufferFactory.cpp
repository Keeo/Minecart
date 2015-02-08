#include "stdafx.h"
#include "FrameBufferFactory.h"

namespace opengl
{


	std::shared_ptr<FrameBuffer> FrameBufferFactory::buildFramebuffer()
	{
		std::shared_ptr<FrameBuffer> fb = std::make_shared<FrameBuffer>();
		fb->generate();
		fb->bind();

		std::shared_ptr<Texture> tex = TextureFactory::buildColorAttachment(Constants::RESOLUTION_X, Constants::RESOLUTION_Y);
		
		tex->bind();
		
		fb->attachColor(tex);

		fb->finalizeDrawBuffers();

		fb->check();
		tex->unbind();
		fb->unbind();

		return fb;
	}
}
