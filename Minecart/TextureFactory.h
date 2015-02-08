#pragma once

#include "Constants.h"
#include "Texture.h"

namespace opengl
{

	class TextureFactory
	{
	public:
		static std::unique_ptr<Texture> buildFromImage(sf::Image& image);
		static std::unique_ptr<Texture> buildColorAttachment(int x, int y);
	};

}
