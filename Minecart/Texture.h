#pragma once

#include "OpenGLObject.h"

namespace opengl
{

	class Texture : public OpenGLObject
	{
		int width_;
		int height_;

	public:
		void loadFromImage(sf::Image& image);
		void bind();
		void unbind();
		void generate();
		
		void setWrap(bool repeats, bool repeatt);
		void setFilter(bool smooth);

		void specify(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);
		void specifyRGBA();
		void specifyRGB();
		void specifyDepth();

		Texture(int width = 0, int height = 0);
		~Texture();

	};

}
