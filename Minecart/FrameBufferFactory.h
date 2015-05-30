//----------------------------------------------------------------------------------------
/**
* \file       FramebufferFactory.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class that can generate framebuffers.
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "Constants.h"
#include "FrameBuffer.h"
#include "TextureFactory.h"

namespace opengl
{

	class FrameBufferFactory
	{
	public:
		/// builds basic framebuffer
		static std::shared_ptr<FrameBuffer> buildFramebuffer();
		/// builds half size framebuffer
		static std::shared_ptr<FrameBuffer> buildSmallFramebuffer();
		/// builds framebuffer for shadow mapping
		static std::shared_ptr<FrameBuffer> buildShadowFramebuffer();
		/// build framebuffer for gaussian blur
		static std::shared_ptr<FrameBuffer> buildFullBlurFramebuffer();
	};

}
