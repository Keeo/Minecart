#pragma once

#include "Constants.h"
#include "Drawable.h"
#include "MeshStruct.h"

namespace view
{

	class BoundingBox : public view::Drawable
	{
		static GLfloat boundingVertexData[];
		static GLuint boundingIndexData[];

		void moveToGpu();
		void makeVAO();
	public:

		BoundingBox();
		~BoundingBox();
	};

}
