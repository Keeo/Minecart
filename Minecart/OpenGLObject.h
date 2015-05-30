//----------------------------------------------------------------------------------------
/**
* \file       OpenGLObject.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class can represents any opengl object.
*/
//----------------------------------------------------------------------------------------
#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#define glCheck() glCheckError(__FILE__, __LINE__);

namespace opengl
{

	class OpenGLObject
	{
	protected:
		GLuint id_ = 0; ///< objects id
		bool active_ = false; ///< active status

		void glCheckError(const char* file, unsigned int line);

	public:
		/// bind object
		void bind();

		/// unbind object
		void unbind();

		/// check if object is active
		bool active();

		/// returns objects id
		GLuint id() const;

		OpenGLObject();
		~OpenGLObject();
	};

}
