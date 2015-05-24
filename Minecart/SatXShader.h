#pragma once

#include "BaseShader.h"

namespace view
{

	class SatXShader : public BaseShader
	{
		GLint pass_ = -1;
		GLint scale_ = -1;
	public:
		void bind(int pass);
		SatXShader();
		~SatXShader();
	};

}
