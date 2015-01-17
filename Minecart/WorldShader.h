#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#include "BaseShader.h"
#include "IEventMessagingSystem.h"
#include "EEvent.h"
#include "Camera.h"
#include "Window.h"

namespace view
{

	class WorldShader : public BaseShader
	{

		sf::Image img_;
		sf::Texture tex_;

	public:

	


		WorldShader();
		~WorldShader();
	};

}
