//----------------------------------------------------------------------------------------
/**
* \file       SatY.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class that will use SatY shader.
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "BaseShader.h"

namespace view
{

	class SatYShader : public BaseShader
	{
		GLint pass_ = -1;
		GLint scale_ = -1;
	public:
		void bind(int pass);
		SatYShader();
		~SatYShader();
	};

}
