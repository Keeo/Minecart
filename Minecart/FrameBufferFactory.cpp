#include "stdafx.h"
#include "FrameBufferFactory.h"

namespace opengl
{


	std::shared_ptr<FrameBuffer> FrameBufferFactory::buildFramebuffer()
	{
		std::shared_ptr<FrameBuffer> fb = std::make_shared<FrameBuffer>();
		fb->generate();
		fb->bind();

		std::shared_ptr<Texture> color = TextureFactory::buildByteColorAttachment(Constants::RESOLUTION_X, Constants::RESOLUTION_Y);
		color->bind();
		fb->attachColor(color, 0);

		std::shared_ptr<Texture> tex = TextureFactory::buildFloatColorAttachment(Constants::RESOLUTION_X, Constants::RESOLUTION_Y);
		tex->bind();
		fb->attachColor(tex, 1);

		fb->attachDepthDummy();

		fb->check();

		tex->unbind();
		color->unbind();
		fb->unbind();

		return fb;
	}

	std::shared_ptr<FrameBuffer> FrameBufferFactory::buildSmallFramebuffer()
	{
		std::shared_ptr<FrameBuffer> fb = std::make_shared<FrameBuffer>();
		fb->generate();
		fb->bind();

		std::shared_ptr<Texture> color = TextureFactory::buildByteColorAttachment(Constants::RESOLUTION_X / 2, Constants::RESOLUTION_Y / 2, true);
		color->bind();
		fb->attachColor(color, 0);

		std::shared_ptr<Texture> color2 = TextureFactory::buildByteColorAttachment(Constants::RESOLUTION_X / 2, Constants::RESOLUTION_Y / 2, true);
		color2->bind();
		fb->attachColor(color2, 1);

		fb->check();
		color->unbind();
		color2->unbind();
		fb->unbind();

		return fb;
	}

	std::shared_ptr<FrameBuffer> FrameBufferFactory::buildShadowFramebuffer()
	{
		std::shared_ptr<FrameBuffer> fb = std::make_shared<FrameBuffer>();
		fb->generate();
		fb->bind();

		std::shared_ptr<Texture> color = TextureFactory::buildShadowAttachment(Constants::RESOLUTION_X, Constants::RESOLUTION_Y);
		color->bind();
		fb->attachColor(color, 0);

		fb->check();
		color->unbind();
		fb->unbind();

		return fb;
	}
}
