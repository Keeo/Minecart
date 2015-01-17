#pragma once

#include <memory>

#include "boost/circular_buffer.hpp"

#include "Model.h"
#include "WorldShader.h"
#include "SimpleShader.h"
#include "IEventMessagingSystem.h"
#include "BoundingBox.h"


namespace view
{

	class AdvancedDrawer : model::IEventMessagingSystem
	{
		WorldShader worldShader_;
		SimpleShader simpleShader_;
		BoundingBox box_;

	public:

		void draw(std::shared_ptr<model::Model> model);

		void draw(model::Chunk* chunk);

		void drawBoundingBoxFor(model::Chunk* chunk);


		AdvancedDrawer();
		~AdvancedDrawer();
	};

}
