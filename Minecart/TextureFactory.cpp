#include "stdafx.h"
#include "TextureFactory.h"

namespace opengl
{

	std::unique_ptr<Texture> TextureFactory::buildFromImage(sf::Image& image)
	{
		sf::Vector2u& dim = image.getSize();
		std::unique_ptr<Texture> tex = std::make_unique<Texture>(dim.x, dim.y);
		tex->generate();

		tex->bind();
		tex->specifyRGBA();
		tex->setFilter(false);
		tex->setWrap(true, true);
		tex->loadFromImage(image);
		tex->unbind();

		return tex;
	}

	std::unique_ptr<Texture> TextureFactory::buildColorAttachment(int x, int y)
	{
		std::unique_ptr<Texture> tex = std::make_unique<Texture>(x, y);
		tex->generate();

		tex->bind();
		tex->specifyRGBAFloat();
		tex->setFilter(false);
		tex->setWrap(true, true);
		tex->unbind();

		return tex;
	}

}
