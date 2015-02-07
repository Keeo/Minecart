#include "stdafx.h"
#include "RenderBuffer.h"

namespace opengl
{

	RenderBuffer::RenderBuffer()
	{
		glGenRenderbuffers(1, &id_);
		glBindRenderbuffer(GL_RENDERBUFFER, id_);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id_);
	}


	RenderBuffer::~RenderBuffer()
	{
	}

}
