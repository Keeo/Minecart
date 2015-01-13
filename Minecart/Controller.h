#pragma once

#include "Model.h"
#include "GameTime.h"
#include "IEventMessagingSystem.h"
#include "View.h"

class Controller : model::IEventMessagingSystem
{
	std::shared_ptr<model::Model> model_;
	std::unique_ptr<view::View> view_;
	bool running_;

public:

	Controller();

	~Controller();

	void stop();
	void run();

};

