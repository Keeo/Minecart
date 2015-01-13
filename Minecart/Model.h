#pragma once

#include <memory>

#include "GameTime.h"
#include "World.h"

namespace model
{

	class Model
	{

		std::shared_ptr<World> world_;
		WorldBuilder worldBuilder_;

	public:

		std::shared_ptr<World> getWorld();

		Model();

		~Model();

		void update(const GameTime&);

	};

}

