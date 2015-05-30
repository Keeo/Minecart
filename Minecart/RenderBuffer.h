//----------------------------------------------------------------------------------------
/**
* \file       RenderBuffer.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class can represents render buffer.
*/
//----------------------------------------------------------------------------------------
#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

namespace opengl
{

	class RenderBuffer
	{
		GLuint id_; ///< render buffer id
		
	public:
		RenderBuffer();
		~RenderBuffer();
	};

}
