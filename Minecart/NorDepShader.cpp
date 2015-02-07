#include "stdafx.h"
#include "NorDepShader.h"

namespace view
{

	NorDepShader::NorDepShader() : BaseShader("./shaders/nor_dep_texture.vert", "./shaders/nor_dep_texture.frag")
	{
	}


	NorDepShader::~NorDepShader()
	{
	}

}
