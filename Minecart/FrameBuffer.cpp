#include "stdafx.h"
#include "FrameBuffer.h"

namespace opengl
{

	FrameBuffer::FrameBuffer()
	{
	}

	void FrameBuffer::setPassShadow()
	{
		assert(active_);
		glViewport(0, 0, Constants::RESOLUTION_X, Constants::RESOLUTION_Y);

		GLuint attachments[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, attachments);
	}

	void FrameBuffer::setPassSSAO()
	{
		assert(active_);
		glViewport(0, 0, Constants::RESOLUTION_X / 2, Constants::RESOLUTION_Y / 2);

		GLuint attachments[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, attachments);
	}

	void FrameBuffer::setPassDisplay()
	{
		assert(active_);
		glViewport(0, 0, Constants::RESOLUTION_X, Constants::RESOLUTION_Y);

		GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);
	}

	void FrameBuffer::generate()
	{
		glGenFramebuffers(1, &id_);
	}

	FrameBuffer::~FrameBuffer()
	{
	}

	void FrameBuffer::attachColor(std::shared_ptr<opengl::Texture> texture, GLuint colorNumber)
	{
		attach(texture, GL_COLOR_ATTACHMENT0 + colorNumber);
	}

	void FrameBuffer::attachDepth(std::shared_ptr<opengl::Texture> texture)
	{
		attach(texture, GL_DEPTH_ATTACHMENT);
	}

	void FrameBuffer::attach(std::shared_ptr<opengl::Texture> texture, GLuint attachmentType)
	{
		assert(active_);
		attachedTextures_.insert(std::make_pair(attachmentType - GL_COLOR_ATTACHMENT0, texture));
		glFramebufferTexture(GL_FRAMEBUFFER, attachmentType, texture->id(), 0);
	}

	void FrameBuffer::attachDepthDummy()
	{
		assert(active_);
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Constants::RESOLUTION_X, Constants::RESOLUTION_Y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
	}

	void FrameBuffer::bind()
	{
		assert(id_ != 0);
		glBindFramebuffer(GL_FRAMEBUFFER, id_);
		active_ = true;
	}

	void FrameBuffer::unbind()
	{
		assert(active_);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		active_ = false;
	}

	void FrameBuffer::setSize(int width, int height)
	{
		assert(active_);
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, width);
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, height);
		//glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, samples);
	}

	void FrameBuffer::activateAttachments(std::vector<GLuint> attachments)
	{
		assert(active_);
		assert(attachments.size() > 0);
		glDrawBuffers(static_cast<GLsizei>(attachments.size()), attachments.data());
	}

	void FrameBuffer::check()
	{
		GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (e != GL_FRAMEBUFFER_COMPLETE) {
			printf("There is a problem with the FBO\n");
		}
	}

	std::map<GLuint, std::shared_ptr<Texture>>* FrameBuffer::attachedTextures()
	{
		return &attachedTextures_;
	}

}
