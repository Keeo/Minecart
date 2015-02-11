#include "stdafx.h"
#include "TextureShader.h"

namespace view
{

	TextureShader::TextureShader() : BaseShader("./shaders/quad_pass.vert", "./shaders/quad_pass.frag")
	{
	}


	TextureShader::~TextureShader()
	{
	}

}
