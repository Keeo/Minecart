#include "stdafx.h"
#include "WorldShader.h"

namespace view
{
	WorldShader::WorldShader() : BaseShader("./shaders/world.vert", "./shaders/world.frag")
	{
		img_.loadFromFile("./textures/cubes.png");
		tex_.loadFromImage(img_);
		grlImg_.loadFromFile("./textures/gril.png");
		grl_.loadFromImage(grlImg_);

		BaseShader::bind();
		bindTexture("sampler", tex_, 0);
		bindTexture("gril", grl_, 1);
		BaseShader::unbind();
	}

	sf::Shader* WorldShader::getShader()
	{
		return &shader_;
	}

	WorldShader::~WorldShader()
	{
	}

}
