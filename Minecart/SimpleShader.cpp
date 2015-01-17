#include "stdafx.h"
#include "SimpleShader.h"

namespace view
{

	SimpleShader::SimpleShader() : BaseShader("./shaders/simple.vert", "./shaders/simple.frag")
	{
	}


	SimpleShader::~SimpleShader()
	{
	}

}
