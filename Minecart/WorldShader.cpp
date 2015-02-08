#include "stdafx.h"
#include "WorldShader.h"

namespace view
{
	WorldShader::WorldShader() : BaseShader("./shaders/world.vert", "./shaders/world.frag")
	{
		img_.loadFromFile("./textures/cubes.png");
		tex_ = opengl::TextureFactory::buildFromImage(img_);
		grlImg_.loadFromFile("./textures/gril.png");
		grl_ = opengl::TextureFactory::buildFromImage(grlImg_);
	}


	void WorldShader::bind()
	{
		BaseShader::bind();
		bindTexture("sampler", *tex_, 0);
		bindTexture("gril", *grl_, 1);
	}

	sf::Shader* WorldShader::getShader()
	{
		return &shader_;
	}

	WorldShader::~WorldShader()
	{
	}

}
