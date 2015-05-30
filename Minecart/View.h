//----------------------------------------------------------------------------------------
/**
* \file       View.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class responsible for rendering.
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "Model.h"

#include "IEventMessagingSystem.h"
#include "AdvancedDrawer.h"
#include "Window.h"
#include "MeshManager.h"
#include "TestDrawer.h"
#include "ShadowDrawer.h"

namespace view
{

	class View : model::IEventMessagingSystem
	{
		std::unique_ptr<Camera> camera_;
		std::unique_ptr<AdvancedDrawer> advancedDrawer_;
		std::unique_ptr<TestDrawer> testDrawer_;
		std::unique_ptr<ShadowDrawer> shadowDrawer_;
		std::unique_ptr<Window> window_;
		MeshManager meshManager;

	public:
		void setActive(bool active);
		void update(const GameTime&);
		void draw(std::shared_ptr<model::Model> model);

		View();
		~View();
	};

}
