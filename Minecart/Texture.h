//----------------------------------------------------------------------------------------
/**
* \file       Texture.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class can represents textures.
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "OpenGLObject.h"

namespace opengl
{

	class Texture : public OpenGLObject
	{
		int width_; ///< textures width
		int height_; ///< textures height

	public:
		void loadFromImage(sf::Image& image);
		/// binds texture
		void bind();

		/// unbinds texture
		void unbind();

		/// generate texture
		void generate();
		
		/// sets wrap properties
		void setWrap(bool repeats, bool repeatt);

		/// sets filter properties
		void setFilter(bool smooth);

		/// specify texture
		void specify(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);

		/// helper for specify
		void specifyRGBAFloat();
		/// helper for specify
		void specifyRGFloat();
		/// helper for specify
		void specifyRGBA();
		/// helper for specify
		void specifyRGB();
		/// helper for specify
		void specifyDepth();

		/// Texture constructor
		Texture(int width = 0, int height = 0);
		/// Texture destructor
		~Texture();

	};

}
