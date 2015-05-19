#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#include "Constants.h"
#include "OpenGLObject.h"
#include "Texture.h"

namespace opengl
{

	class FrameBuffer : public OpenGLObject
	{
		//std::vector<std::shared_ptr<opengl::Texture>> attachedTextures_;
		std::map<GLuint, std::shared_ptr<opengl::Texture>> attachedTextures_;

		GLuint depthrenderbuffer;

	public:

		void setPassShadow();
		void setPassSSAO();
		void setPassDisplay();

		void check();

		void bind();
		void unbind();

		void setSize(int width, int height);
		
		void attach(std::shared_ptr<opengl::Texture> texture, GLuint attachmentType);
		void attachColor(std::shared_ptr<opengl::Texture> texture, GLuint colorNumber = 0);
		void attachDepth(std::shared_ptr<opengl::Texture> texture);
		void attachDepthDummy();

		void generate();

		void activateAttachments(std::vector<GLuint> attachments);

		std::map<GLuint, std::shared_ptr<Texture>>* attachedTextures();

		FrameBuffer();
		~FrameBuffer();
	};

}
