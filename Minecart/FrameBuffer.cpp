#include "stdafx.h"
#include "FrameBuffer.h"

namespace opengl
{

	FrameBuffer::FrameBuffer()
	{
	}

	void FrameBuffer::generate()
	{
		glGenFramebuffers(1, &id_);
	}

	FrameBuffer::~FrameBuffer()
	{
	}

	void FrameBuffer::attachColor(const opengl::Texture& texture, GLuint colorNumber)
	{
		attach(texture, GL_COLOR_ATTACHMENT0 + colorNumber);
	}

	void FrameBuffer::attachDepth(const opengl::Texture& texture)
	{
		attach(texture, GL_DEPTH_ATTACHMENT);
	}

	void FrameBuffer::attach(const opengl::Texture& texture, GLuint attachmentType)
	{
		assert(active_);
		glFramebufferTexture(GL_DRAW_FRAMEBUFFER, attachmentType, texture.id(), 0);
	}

	void FrameBuffer::bind()
	{
		assert(!active_);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id_);
		active_ = true;
	}

	void FrameBuffer::unbind()
	{
		assert(active_);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		active_ = false;
	}

	void FrameBuffer::setSize(int width, int height, int samples)
	{
		assert(active_);
		glFramebufferParameteri(GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, width);
		glFramebufferParameteri(GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, height);
		glFramebufferParameteri(GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, samples);
	}

	void FrameBuffer::activateAttachments(std::vector<GLuint> attachments)
	{
		assert(active_);
		assert(attachments.size() > 0);
		glDrawBuffers(static_cast<GLsizei>(attachments.size()), attachments.data());
	}

	void FrameBuffer::check()
	{
		bind();
		GLenum e = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
		if (e != GL_FRAMEBUFFER_COMPLETE) {
			printf("There is a problem with the FBO\n");
		}
	}

}
