//----------------------------------------------------------------------------------------
/**
* \file       ShadowDrawer.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class that will draw scene with shadows.
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
#include "DepthShader.h"
#include "IEventMessagingSystem.h"
#include "BoundingBox.h"
#include "FrameBuffer.h"
#include "FrameBufferFactory.h"
#include "TextureFactory.h"
#include "ScreenQuad.h"
#include "SSAOShader.h"
#include "SatXShader.h"
#include "SatYShader.h"
#include "BlurXShader.h"
#include "BlurYShader.h"
#include "TextureShader.h"
#include "PointLight.h"
#include "LightShader.h"

namespace view
{

	class View;

	class ShadowDrawer : model::IEventMessagingSystem
	{
		WorldShader worldShader_;
		SimpleShader simpleShader_;
		NorDepShader norDepShader_;
		DepthShader depthShader_;
		SSAOShader ssaoShader_;
		BlurXShader blurXShader_;
		BlurYShader blurYShader_;
		SatXShader satXShader_;
		SatYShader satYShader_;
		LightShader lightShader_;
		TextureShader texShader_;
		BoundingBox box_;
		ScreenQuad sc_;
		std::shared_ptr<opengl::FrameBuffer> shadowBuffer_;

		/// Draw scene
		void draw(std::vector<model::Chunk*>& chunks, BaseShader* shader);
	public:

		void draw(std::shared_ptr<model::Model> model, view::View* view);

		ShadowDrawer();
		~ShadowDrawer();
	};

}
