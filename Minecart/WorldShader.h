#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#include "BaseShader.h"
#include "IEventMessagingSystem.h"
#include "EEvent.h"
#include "Camera.h"
#include "Window.h"
#include "Texture.h"
#include "TextureFactory.h"

namespace view
{

	class WorldShader : public BaseShader
	{

		sf::Image img_;
		sf::Image grlImg_;
		std::unique_ptr<opengl::Texture> tex_;
		std::unique_ptr<opengl::Texture> grl_;

	public:

		sf::Shader* getShader();
		void bind();

		WorldShader();
		~WorldShader();
	};

}
