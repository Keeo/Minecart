#pragma once

#include "Constants.h"
#include "FrameBuffer.h"
#include "TextureFactory.h"

namespace opengl
{

	class FrameBufferFactory
	{
	public:
		static std::shared_ptr<FrameBuffer> buildFramebuffer();
	};

}
