#pragma once

#include <glm\vec3.hpp>

#include "IEventMessagingSystem.h"
#include "GameTime.h"

namespace model {

	using namespace glm;

	class GameObject : protected IEventMessagingSystem
	{

	protected:
		vec3 position_;
		vec3 direction_;

		virtual void update(const GameTime&) = 0;
		virtual void draw() = 0;

		GameObject();
		virtual ~GameObject();

	};

}
