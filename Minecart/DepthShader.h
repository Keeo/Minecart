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
