#include "stdafx.h"
#include "View.h"

namespace view
{

	View::View()
	{
		window_ = std::make_unique<Window>();
		camera_ = std::make_unique<Camera>();
		advancedDrawer_ = std::make_unique<AdvancedDrawer>();
		testDrawer_ = std::make_unique<TestDrawer>();
	}

	View::~View()
	{
	}

	void View::setActive(bool active)
	{
		window_->setActive(active);
	}

	void View::update(const GameTime& gameTime)
	{
		window_->update();
		camera_->update(gameTime);
	}

	void View::draw(std::shared_ptr<model::Model> model)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Why am i clearing it here?
		advancedDrawer_->condDraw(model);
		//testDrawer_->draw(model, this);
		int err = glGetError();
		if (err && err != 1282) {
			std::cout << "GLError: " << err << std::endl;
		}

		window_->draw();
	}

}
