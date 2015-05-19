#include "stdafx.h"
#include "PointLight.h"

namespace model
{

	void PointLight::update(const GameTime& gameTime)
	{
		float move_speed = 10.0f;
		float delta = gameTime.asSeconds();
		glm::vec3 t = position_;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) position_.x -= move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) position_.x += move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) position_.z += move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) position_.z -= move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) position_.y += move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) position_.y -= move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
			view::CameraData cd;
			Post(EEvent::FetchCameraData, &cd, 0);
			assert(cd.position != NULL);
			position_ = *cd.position;
			std::cout << glm::to_string(position_) << std::endl;
		}
	}

	void PointLight::getLightPosition(void* data)
	{
		glm::vec3* pos = (glm::vec3*) data;
		*pos = position_;
	}

	void PointLight::draw()
	{

	}

	PointLight::PointLight()
	{
		Register(EEvent::FetchLightData, this, (model::Callback) & PointLight::getLightPosition);
	}


	PointLight::~PointLight()
	{
	}

}
