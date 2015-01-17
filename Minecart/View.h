#pragma once

#include "Model.h"

#include "Drawer.h"
#include "AdvancedDrawer.h"
#include "Window.h"
#include "MeshManager.h"

namespace view
{

	class View
	{
		std::unique_ptr<Camera> camera_;
		std::unique_ptr<Drawer> drawer_;
		std::unique_ptr<AdvancedDrawer> advancedDrawer_;
		std::unique_ptr<Window> window_;
		MeshManager meshManager;

	public:

		void update(const GameTime&);
		void draw(std::shared_ptr<model::Model> model);

		View();
		~View();
	};

}
