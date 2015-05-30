//----------------------------------------------------------------------------------------
/**
* \file       FrameBuffer.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class that represents framebuffer.
*/
//----------------------------------------------------------------------------------------
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
		std::map<GLuint, std::shared_ptr<opengl::Texture>> attachedTextures_; ///< attached textures

		GLuint depthrenderbuffer; ///< depth texture

	public:
		/// sets pass for shadow rendering
		void setPassShadow();

		/// sets pass for ssao rendering
		void setPassSSAO();

		/// sets pass for dispaly rendering
		void setPassDisplay();

		/// check framebuffer
		void check();

		/// binds framebuffer
		void bind();

		/// unbinds framebuffer
		void unbind();

		/// sets size of framebuffer
		void setSize(int width, int height);
		
		/// attaches texture
		void attach(std::shared_ptr<opengl::Texture> texture, GLuint attachmentType);

		/// attaches color textures
		void attachColor(std::shared_ptr<opengl::Texture> texture, GLuint colorNumber = 0);

		/// attaches depth texture
		void attachDepth(std::shared_ptr<opengl::Texture> texture);

		/// attaches basic depth texture
		void attachDepthDummy();

		/// generate framebuffer
		void generate();

		/// activate attachments
		void activateAttachments(std::vector<GLuint> attachments);

		/// getter for attached textures
		std::map<GLuint, std::shared_ptr<Texture>>* attachedTextures();

		FrameBuffer();
		~FrameBuffer();
	};

}
