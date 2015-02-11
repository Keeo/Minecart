#include "stdafx.h"
#include "SSAOShader.h"

namespace view
{

	SSAOShader::SSAOShader() : BaseShader("./shaders/quad_pass.vert", "./shaders/ssao_texture.frag")
	{
		img_.loadFromFile("./textures/noise.png");
		tex_ = opengl::TextureFactory::buildFromImage(img_);
	}

	void SSAOShader::bind()
	{
		sf::Shader::bind(&shader_);
		bindTexture("rnm", *tex_, 0);
	}

	SSAOShader::~SSAOShader()
	{
	}

}
