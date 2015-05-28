#include "stdafx.h"
#include "PointLight.h"

namespace model
{

	void PointLight::update(const GameTime& gameTime)
	{
		float move_speed = 10.0f;
		float delta = gameTime.asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) position_.x -= move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) position_.x += move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) position_.z += move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) position_.z -= move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) position_.y += move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) position_.y -= move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
			view::CameraData cd;
			Post(EEvent::FetchCameraData, &cd, 0);
			assert(cd.position != NULL);
			assert(cd.direction != NULL);
			position_ = *cd.position;
			direction_ = *cd.direction;
			std::cout << "pos: " << glm::to_string(position_) << " dir:" << glm::to_string(direction_) << std::endl;
		}
	}

	void PointLight::getLightPosition(void* data)
	{
		view::CameraData* cameraData = (view::CameraData*)data;
		cameraData->position = &position_;
		cameraData->direction = &direction_;
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
