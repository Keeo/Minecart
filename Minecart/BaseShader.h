#pragma once

#include <GL\glew.h>
#include <SFML\Graphics.hpp>

#include "Camera.h"
#include "IEventMessagingSystem.h"
#include "Texture.h"

namespace view
{

	class BaseShader : public model::IEventMessagingSystem
	{

		std::map<std::string, GLint> places_;

		GLint findUniform(std::string& name);

	protected:
		sf::Shader shader_;
		GLint shaderId_ = -1;

		GLint modelLoc_ = -1;
		GLint viewLoc_ = -1;
		GLint projectionLoc_ = -1;
		GLint camPositionLoc_ = -1;
	public:
		
		void bind();
		void unbind();
		void loadModelMatrix(glm::mat4* model);

		void bindTexture(std::string place, opengl::Texture& texture, GLint order = 0);

		BaseShader(std::string vertex, std::string fragment);
		~BaseShader();
	};

}
