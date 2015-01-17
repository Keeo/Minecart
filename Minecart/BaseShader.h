#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#include "Camera.h"
#include "IEventMessagingSystem.h"

namespace view
{

	class BaseShader : public model::IEventMessagingSystem
	{
	protected:
		sf::Shader shader_;
		GLint shaderId_ = -1;

		GLint modelLoc_ = -1;
		GLint viewLoc_ = -1;
		GLint projectionLoc_ = -1;
	public:
		
		void bind();
		void unbind();
		void loadModelMatrix(glm::mat4* model);

		BaseShader(std::string vertex, std::string fragment);
		~BaseShader();
	};

}
