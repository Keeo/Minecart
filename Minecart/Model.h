#pragma once

#include <memory>

#include "GameTime.h"
#include "World.h"
#include "PoolGateway.h"


namespace model
{

	class Model
	{

		std::shared_ptr<World> world_;
		WorldBuilder worldBuilder_;
		PoolGateway poolGateway_;

	public:

		std::shared_ptr<World> getWorld();

		Model();

		~Model();

		void update(const GameTime&);

	};

}
