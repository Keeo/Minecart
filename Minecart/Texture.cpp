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

	void Texture::loadFromImage(sf::Image& image, bool repeat, bool smooth)
	{
		if (id_ == 0) generate();

		width_ = image.getSize().x;
		height_ = image.getSize().y;
		bind();
		specifyRGBA();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		unbind();
	}

	void Texture::specifyDepth()
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width_, height_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	void Texture::specifyRGBA()
	{
		specify(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}

	void Texture::specify(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
	{
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
