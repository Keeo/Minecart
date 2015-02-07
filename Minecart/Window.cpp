#include "stdafx.h"
#include "Window.h"

namespace view {

	Window::Window()
	{
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 3;
		settings.minorVersion = 3;
		window_.create(sf::VideoMode(Constants::RESOLUTION_X, Constants::RESOLUTION_Y), "Mine]|[craft", Constants::FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Default, settings);
		window_.setMouseCursorVisible(Constants::SHOW_MOUSE);
		window_.setActive();

		glewExperimental = GL_TRUE;
		glewInit();

		// create the window
		window_.setVerticalSyncEnabled(false);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);

		glFrontFace(GL_CCW);

		glClearColor(0.f, 0.1f, 0.2f, .1f);

		sf::Texture::getMaximumSize(); // fix for losing active
		sf::Shader::isAvailable();
		window_.setActive();

	}

	Window::Window(const Window& orig)
	{
	}

	Window::~Window()
	{
	}

	void Window::draw()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		window_.display();
	}

	void Window::setActive(bool active)
	{
		window_.setActive(active);
	}

	void Window::update()
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window_.close();
				Post(EEvent::Shutdown, 0, 0);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window_.close();
			Post(EEvent::Shutdown, 0, 0);
		}
	}

}
