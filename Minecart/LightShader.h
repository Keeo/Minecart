#pragma once

#include "BaseShader.h"
#include <boost/algorithm/clamp.hpp>

namespace view
{

	class LightShader : public BaseShader
	{
		GLint linStepBleedPos_ = -1;
		GLint maxVariancePos_ = -1;
		GLint blurStepPos_ = -1;

		float linStepBleed_ = 0.5f;
		float blurStep_ = 2.0f;
		float maxVariance_ = 0.00005f;
		void configVals();
	public:
		void bind();
		LightShader();
		~LightShader();
	};

}
