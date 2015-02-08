#pragma once

#include <memory>
#include <iomanip>

#include "SFML/System.hpp"
#include "boost/circular_buffer.hpp"

#include "Model.h"
#include "WorldShader.h"
#include "SimpleShader.h"
#include "NorDepShader.h"
#include "IEventMessagingSystem.h"
#include "BoundingBox.h"
#include "FrameBuffer.h"
#include "FrameBufferFactory.h"

namespace view
{

	class View;

	class TestDrawer : model::IEventMessagingSystem
	{
		WorldShader worldShader_;
		SimpleShader simpleShader_;
		NorDepShader norDepShader_;
		BoundingBox box_;
		std::shared_ptr<opengl::FrameBuffer> frameBuffer_;


		void draw(std::vector<model::Chunk*>& chunks, BaseShader* shader);
	public:

		void draw(std::shared_ptr<model::Model> model, view::View* view);

		TestDrawer();
		~TestDrawer();
	};

}