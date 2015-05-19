#include "stdafx.h"
#include "Texture.h"

namespace opengl
{

	Texture::Texture(int width, int height) : width_(width), height_(height)
	{
	}

	void Texture::generate()
	{
		glGenTextures(1, &id_);
	}

	void Texture::loadFromImage(sf::Image& image)
	{
		assert(width_ == image.getSize().x);
		assert(height_ == image.getSize().y);
		assert(active_);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	}

	void Texture::setFilter(bool smooth)
	{
		assert(active_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
	}

	void Texture::setWrap(bool repeats, bool repeatt)
	{
		assert(active_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeats ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeatt ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	}

	void Texture::specifyDepth()
	{
		specify(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width_, height_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	void Texture::specifyRGB()
	{
		specify(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}

	void Texture::specifyRGBA()
	{
		specify(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}

	void Texture::specifyRGBAFloat()
	{
		specify(GL_TEXTURE_2D, 0, GL_RGBA16F, width_, height_, 0, GL_RGBA, GL_FLOAT, NULL);
	}

	void Texture::specifyRGFloat()
	{
		specify(GL_TEXTURE_2D, 0, GL_RG32F, width_, height_, 0, GL_RG, GL_FLOAT, NULL);
	}

	void Texture::specify(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
	{
		assert(width_ * height_ != 0);
		assert(active_);
		glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, id_);
		active_ = true;
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		active_ = false;
	}

	Texture::~Texture()
	{
	}

}
