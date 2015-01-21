#pragma once

#include "Constants.h"
#include "Drawable.h"
#include "MeshStruct.h"

namespace view
{

	class BoundingBox : view::Drawable
	{
		static GLfloat boundingVertexData[];
		static GLuint boundingIndexData[];

		void moveToGpu();
		void makeVAO();
		
	public:
		
		void draw();

		BoundingBox();
		~BoundingBox();
	};

}
