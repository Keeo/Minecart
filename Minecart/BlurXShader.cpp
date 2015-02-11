#include "stdafx.h"
#include "BlurXShader.h"

namespace view
{

	BlurXShader::BlurXShader() : BaseShader("./shaders/quad_pass.vert", "./shaders/blurx.frag")
	{
	}


	BlurXShader::~BlurXShader()
	{
	}

}
