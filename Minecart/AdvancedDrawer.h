#pragma once

#include <memory>
#include <iomanip>

#include "SFML/System.hpp"
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

		std::vector<GLuint> query_;

	public:

		void condDraw(std::shared_ptr<model::Model> model);

		void draw(std::shared_ptr<model::Model> model);

		void draw(model::Chunk* chunk);

		void drawBoundingBoxFor(model::Chunk* chunk);

		inline bool isCullable(const CameraData& cd, const glm::vec3& center);

		AdvancedDrawer();
		~AdvancedDrawer();
	};

}
