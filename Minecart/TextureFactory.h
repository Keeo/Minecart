#pragma once

#include "Constants.h"
#include "Texture.h"

namespace opengl
{

	class TextureFactory
	{
	public:
		static std::unique_ptr<Texture> buildFromImage(sf::Image& image);
		static std::unique_ptr<Texture> buildFloatColorAttachment(int x, int y);
		static std::unique_ptr<Texture> buildByteColorAttachment(int x, int y, bool filter = false);
		static std::unique_ptr<Texture> buildShadowAttachment(int x, int y, bool filter = false);
	};

}
