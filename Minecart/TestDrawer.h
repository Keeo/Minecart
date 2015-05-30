//----------------------------------------------------------------------------------------
/**
* \file       EDirection.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class with test drawer
*/
//----------------------------------------------------------------------------------------
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
#include "TextureFactory.h"
#include "ScreenQuad.h"
#include "SSAOShader.h"
#include "BlurXShader.h"
#include "BlurYShader.h"
#include "TextureShader.h"

namespace view
{

	class View;

	class TestDrawer : model::IEventMessagingSystem
	{
		WorldShader worldShader_;
		SimpleShader simpleShader_;
		NorDepShader norDepShader_;
		SSAOShader ssaoShader_;
		BlurXShader blurXShader_;
		BlurYShader blurYShader_;
		TextureShader texShader_;
		BoundingBox box_;
		ScreenQuad sc_;
		std::shared_ptr<opengl::FrameBuffer> frameBuffer_;
		std::shared_ptr<opengl::FrameBuffer> frameSmallBuffer_;

		void draw(std::vector<model::Chunk*>& chunks, BaseShader* shader);
	public:

		void draw(std::shared_ptr<model::Model> model, view::View* view);

		TestDrawer();
		~TestDrawer();
	};

}
