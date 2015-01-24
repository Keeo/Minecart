#include "stdafx.h"
#include "Model.h"

namespace model
{

	Model::Model()
	{
		world_ = std::make_shared<World>();
		world_->build(&worldBuilder_);
	}


	Model::~Model()
	{
	}
	
	void Model::update(const GameTime& gameTime)
	{
		world_->update(gameTime);
	}

	std::shared_ptr<World> Model::getWorld()
	{
		return world_;
	}

}
