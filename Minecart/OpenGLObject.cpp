#include "stdafx.h"
#include "OpenGLObject.h"

namespace opengl
{

	OpenGLObject::OpenGLObject()
	{
	}


	OpenGLObject::~OpenGLObject()
	{
	}

	void OpenGLObject::bind()
	{
		std::cout << "Warning, binding unnsuported opengl object.";
	}

	void OpenGLObject::unbind()
	{
		std::cout << "Warning, unbinding unnsuported opengl object.";
	}

	bool OpenGLObject::active()
	{
		return active_;
	}

	GLuint OpenGLObject::id() const
	{
		return id_;
	}

	void glCheckError(const char* file, unsigned int line)
	{
		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::string fileString(file);
			std::string error = "unknown error";
			std::string description = "no description";

			switch (errorCode)
			{
			case GL_INVALID_ENUM:
			{
				error = "GL_INVALID_ENUM";
				description = "an unacceptable value has been specified for an enumerated argument";
				break;
			}

			case GL_INVALID_VALUE:
			{
				error = "GL_INVALID_VALUE";
				description = "a numeric argument is out of range";
				break;
			}

			case GL_INVALID_OPERATION:
			{
				error = "GL_INVALID_OPERATION";
				description = "the specified operation is not allowed in the current state";
				break;
			}

			case GL_STACK_OVERFLOW:
			{
				error = "GL_STACK_OVERFLOW";
				description = "this command would cause a stack overflow";
				break;
			}

			case GL_STACK_UNDERFLOW:
			{
				error = "GL_STACK_UNDERFLOW";
				description = "this command would cause a stack underflow";
				break;
			}

			case GL_OUT_OF_MEMORY:
			{
				error = "GL_OUT_OF_MEMORY";
				description = "there is not enough memory left to execute the command";
				break;
			}

			}

			std::cout << "An internal OpenGL call failed in "
				<< fileString.substr(fileString.find_last_of("\\/") + 1) << " (" << line << ") : "
				<< error << ", " << description
				<< std::endl;
		}
	}

}
