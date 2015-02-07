#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#define glCheck() glCheckError(__FILE__, __LINE__);

namespace opengl
{

	class OpenGLObject
	{
	protected:
		GLuint id_ = 0;
		bool active_ = false;

		void glCheckError(const char* file, unsigned int line);

	public:
		
		void bind();
		void unbind();
		bool active();

		GLuint id() const;

		OpenGLObject();
		~OpenGLObject();
	};

}
