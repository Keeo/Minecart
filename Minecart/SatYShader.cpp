#include "stdafx.h"
#include "SatYShader.h"

namespace view
{

	SatYShader::SatYShader() : BaseShader("./shaders/quad_pass.vert", "./shaders/saty.frag")
	{
		pass_ = glGetUniformLocation(shaderId_, "pass");
		scale_ = glGetUniformLocation(shaderId_, "scale");

		//assert(pass_ != -1);
		//assert(cut_ != -1);
	}

	void SatYShader::bind(int pass)
	{
		BaseShader::bind();

		glUniform1iv(pass_, 1, &pass);
		//glUniform2fv(scale_, 1, glm::value_ptr(scale));
	}

	SatYShader::~SatYShader()
	{
	}

}
