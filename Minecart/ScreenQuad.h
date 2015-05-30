//----------------------------------------------------------------------------------------
/**
* \file       ScreenQuad.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class for quad rendering.
*
*  This class can render quad.
*
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "Constants.h"
#include "Drawable.h"
#include "MeshStruct.h"
#include "BaseShader.h"

namespace view
{
	/// Class that can render quad
	class ScreenQuad : view::Drawable
	{
		static GLfloat quadVertexData[]; ///< Vertex positions
		static GLuint quadIndexData[]; ///< Vertex indeces

		/// Transport data to gpu
		void moveToGpu();

		/// Builds Vertex Array Object
		void makeVAO();
		
	public:

		/// Draw quad
		void draw(bool triangles = true);

		/// Contructor
		ScreenQuad();

		/// Destructor
		~ScreenQuad();
	};

}
