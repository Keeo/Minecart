#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>
#include "OpenGLObject.h"
#include "Texture.h"

namespace opengl
{

	class FrameBuffer : public OpenGLObject
	{
	public:

		void bind();
		void unbind();

		void setSize(int width, int height, int samples);
		
		void attach(const opengl::Texture& texture, GLuint attachmentType);
		void attachColor(const opengl::Texture& texture, GLuint colorNumber = 0);
		void attachDepth(const opengl::Texture& texture);

		void check();
		void generate();

		void activateAttachments(std::vector<GLuint> attachments);

		FrameBuffer();
		~FrameBuffer();
	};

}
