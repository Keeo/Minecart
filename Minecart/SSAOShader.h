#pragma once

#include "BaseShader.h"
#include "TextureFactory.h"

namespace view
{

	class SSAOShader : public BaseShader
	{
		sf::Image img_;
		std::unique_ptr<opengl::Texture> tex_;

	public:
		void bind();

		SSAOShader();
		~SSAOShader();
	};

}
