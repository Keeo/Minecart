#pragma once

#include "BaseShader.h"

namespace view
{

	class LightShader : public BaseShader
	{
	public:
		void bind();
		LightShader();
		~LightShader();
	};

}
