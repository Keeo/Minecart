#include "stdafx.h"
#include "WorldShader.h"

namespace view
{
	WorldShader::WorldShader() : BaseShader("./shaders/world.vert", "./shaders/world.frag")
	{
		img_.loadFromFile("./textures/cubes.png");
		tex_.loadFromImage(img_);
		shader_.setParameter("sampler", tex_);
	}

	WorldShader::~WorldShader()
	{
	}

}
