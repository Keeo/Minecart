//----------------------------------------------------------------------------------------
/**
* \file       SatX.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class that will use Depth shader.
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "BaseShader.h"

namespace view
{

	class DepthShader : public BaseShader
	{
	public:
		void bind();
		DepthShader();
		~DepthShader();
	};

}
