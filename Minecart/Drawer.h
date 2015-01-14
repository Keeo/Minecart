#pragma once

#include <memory>

#include "boost/circular_buffer.hpp"

#include "Model.h"
#include "WorldShader.h"
#include "IEventMessagingSystem.h"

namespace view {

	class Drawer : model::IEventMessagingSystem
	{
		WorldShader worldShader_;

	public:

		void draw(std::shared_ptr<model::Model> model);

		void drawB(model::Chunk* chunk);
		void draw(model::Chunk* chunk);

		Drawer();

		~Drawer();

	};

}

