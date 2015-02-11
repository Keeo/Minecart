#include "stdafx.h"
#include "BlurYShader.h"

namespace view
{

	BlurYShader::BlurYShader() : BaseShader("./shaders/quad_pass.vert", "./shaders/blury.frag")
	{
	}


	BlurYShader::~BlurYShader()
	{
	}

}
