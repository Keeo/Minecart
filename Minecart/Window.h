#pragma once

#include <gl/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Constants.h"
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
		void setActive(bool active);
	private:

		sf::RenderWindow window_;

	};


}
