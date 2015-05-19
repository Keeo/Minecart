#pragma once

#include "Camera.h"
#include "glm/ext.hpp"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "GameObject.h"


namespace model
{

	class PointLight : GameObject
	{
		void getLightPosition(void* data);

	public:
		void update(const GameTime& gameTime);
		void draw();
		glm::vec3 getPosition();

		PointLight();
		~PointLight();
	};

}
