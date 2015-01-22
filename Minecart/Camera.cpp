#include "stdafx.h"
#include "Camera.h"

namespace view {

	Camera::Camera()
	{
		positionLast_ = position_ = glm::vec3(6, 7, 8);
		direction_ = glm::vec3(0, 0, 0);
		projection_ = glm::perspective(100.0f, (float)Constants::RESOLUTION_X / (float)Constants::RESOLUTION_Y, 0.1f, 1000.0f);
		view_ = glm::lookAt(position_, direction_, glm::vec3(0, 1, 0));

		Register(EEvent::FetchCameraData, this, (model::Callback) & Camera::getCameraData);
	}

	void Camera::getCameraData(void* data)
	{
		CameraData* cameraData = (CameraData*)data;
		cameraData->position = &position_;
		cameraData->projection = &projection_;
		cameraData->view = &view_;
	}


	void Camera::update(const GameTime& time)
	{
		float delta = time.asSeconds();

		move(delta);
		rotate(delta);

		glm::i32vec3 oldChunk = posToChunk(positionLast_);
		glm::i32vec3 newChunk = posToChunk(position_);
		if (oldChunk != newChunk) {
			Post(EEvent::CameraChangedChunk, &newChunk, 0);
		}
	}

	glm::i32vec3& Camera::posToChunk(glm::vec3& const pos)
	{
#define tc(x) ( x/Constants::CHUNK_SIZE )
		return glm::i32vec3(tc(pos.x), tc(pos.y), tc(pos.z));
	}

	void Camera::move(float& delta)
	{
		float move_speed = 50.0f;

		glm::vec3 axis(0, 0, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) axis += direction_ * move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) axis -= direction_ * move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) axis += right_ * move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) axis -= right_ * move_speed * delta;
		
		positionLast_ = position_;
		position_ += axis;
	}


	void Camera::rotate(float& delta)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

			float x = sf::Mouse::getPosition().x - 500;
			float y = sf::Mouse::getPosition().y - 500;
			sf::Mouse::setPosition(sf::Vector2i(500, 500));

			static float mouse_speed = .002f;
			horizontalAngle_ -= x * mouse_speed;// * delta;
			verticalAngle_ -= y * mouse_speed;// * delta;
			updateDirection();
			
			view_ = glm::lookAt(position_, position_ + direction_, up_);
		}
	}


	void Camera::updateDirection()
	{
		direction_ = glm::vec3(
			cos(verticalAngle_) * sin(horizontalAngle_),
			sin(verticalAngle_),
			cos(verticalAngle_) * cos(horizontalAngle_)
			);

		right_ = glm::vec3(
			sin(horizontalAngle_ - 3.14f / 2.0f),
			0,
			cos(horizontalAngle_ - 3.14f / 2.0f)
			);

		up_ = glm::cross(right_, direction_);
	}


	Camera::~Camera()
	{
	}

}
