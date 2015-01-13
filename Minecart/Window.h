#pragma once

#include <gl/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "IEventMessagingSystem.h"

namespace view {

	class Window : model::IEventMessagingSystem
	{
	public:
		Window();
		Window(const Window& orig);
		virtual ~Window();
		void draw();
		void update();
		void setActive();
	private:

		sf::RenderWindow window_;

	};


}
