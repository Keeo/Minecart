#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#include "IEventMessagingSystem.h"
#include "EEvent.h"
#include "Camera.h"
#include "Window.h"

namespace view
{

	class WorldShader : model::IEventMessagingSystem
	{

		sf::Shader shader_;

		sf::Image img_;
		sf::Texture tex_;

		GLint shaderId_ = -1;

		GLint modelLoc_ = -1;
		GLint viewLoc_ = -1;
		GLint projectionLoc_ = -1;

	public:

		void loadModelMatrix(glm::mat4* model);

		void bind();
		void unbind();

		WorldShader();
		~WorldShader();
	};

}
