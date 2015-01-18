#include "stdafx.h"
#include "Controller.h"


Controller::Controller()
{
	model_ = std::make_shared<model::Model>();
	view_ = std::make_unique<view::View>();
	
}


void Controller::run()
{
	running_ = true;
	Register(EEvent::Shutdown, this, (model::Callback)&Controller::stop);


	sf::Clock clock;
	GameTime gameTime;
	
	while (running_)
	{
		gameTime.time = clock.restart();

		view_->update(gameTime);
		if (!running_) break;

		model_->update(gameTime);
		view_->init(model_);
		view_->draw(model_);
	}
}

void Controller::stop()
{
	running_ = false;
}

Controller::~Controller()
{
}
