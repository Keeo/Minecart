#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

namespace opengl
{

	class RenderBuffer
	{
		GLuint id_;
		
	public:
		RenderBuffer();
		~RenderBuffer();
	};

}
