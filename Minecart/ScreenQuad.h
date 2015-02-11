#pragma once

#include "Constants.h"
#include "Drawable.h"
#include "MeshStruct.h"


namespace view
{

	class ScreenQuad : view::Drawable
	{
		static GLfloat quadVertexData[];
		static GLuint quadIndexData[];

		void moveToGpu();
		void makeVAO();
		
	public:
		void draw(bool triangles = true);

		ScreenQuad();
		~ScreenQuad();
	};

}
