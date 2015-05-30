//----------------------------------------------------------------------------------------
/**
* \file       TextureFactory.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class can generate textures.
*/
//----------------------------------------------------------------------------------------
#pragma once

#include "Constants.h"
#include "Texture.h"

namespace opengl
{

	class TextureFactory
	{
	public:
		/// generate texture from image
		static std::unique_ptr<Texture> buildFromImage(sf::Image& image);
		/// generate float color attachment
		static std::unique_ptr<Texture> buildFloatColorAttachment(int x, int y);
		/// generate byte color attachment
		static std::unique_ptr<Texture> buildByteColorAttachment(int x, int y, bool filter = false);
		/// generate shadow attachment
		static std::unique_ptr<Texture> buildShadowAttachment(int x, int y, bool filter = false);
	};

}
