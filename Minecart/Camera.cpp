#include "stdafx.h"
#include "Camera.h"

namespace view {

	using namespace boost::math::constants;

	Camera::Camera()
	{
		verticalAngle_ = pi<float>();
		horizontalAngle_ = 0;
		up_ = glm::vec3(0, 1, 0);
		positionLast_ = position_ = glm::vec3(6, 7, 8);
		direction_ = glm::vec3(0, 0, 0);
		projection_ = glm::perspective(100.0f, (float)Constants::RESOLUTION_X / (float)Constants::RESOLUTION_Y, 0.1f, 1000.0f);
		view_ = glm::lookAt(position_, direction_, up_);

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			position_ = glm::vec3(215, 256, -150);
			horizontalAngle_ = 0.18399f;
			verticalAngle_ = 3.08559f;
			direction_ = glm::vec3(-0.182676, 0.055972, -0.981579);
		}
		move(delta);
		rotate(delta);

		glm::i32vec3 oldChunk = posToChunk(positionLast_);
		glm::i32vec3 newChunk = posToChunk(position_);
		if (oldChunk != newChunk) {
			Post(EEvent::CameraChangedChunk, &newChunk, 0);
		}
	}

	glm::i32vec3 Camera::posToChunk(const glm::vec3& pos)
	{
#define tc(x) ( x/Constants::CHUNK_SIZE )
		return glm::i32vec3(tc(pos.x), tc(pos.y), tc(pos.z));
	}

	void Camera::move(float& delta)
	{
		float move_speed = 50.0f;

		glm::vec3 axis(0, 0, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) axis -= direction_ * move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) axis += direction_ * move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) axis += right_ * move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) axis -= right_ * move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) axis.y += move_speed * delta;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) axis.y -= move_speed * delta;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) axis *= 4;

		positionLast_ = position_;
		position_ += axis;
	}

	void Camera::rotate(float& delta)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || Constants::FULLSCREEN) {

			float x = static_cast<float>(sf::Mouse::getPosition().x - 500);
			float y = static_cast<float>(sf::Mouse::getPosition().y - 500);
			sf::Mouse::setPosition(sf::Vector2i(500, 500));

			static float mouse_speed = .002f;
			horizontalAngle_ -= x * mouse_speed;// *delta;
			verticalAngle_ -= y * mouse_speed;// *delta;
			verticalAngle_ = boost::algorithm::clamp(verticalAngle_, half_pi<float>(), half_pi<float>() + pi<float>());
			
		}
		updateDirection();

		view_ = glm::lookAt(position_, position_ - direction_, up_);
	}


	void Camera::updateDirection()
	{
		direction_ = glm::vec3(
			cos(verticalAngle_) * sin(horizontalAngle_),
			sin(verticalAngle_),
			cos(verticalAngle_) * cos(horizontalAngle_)
			);

		right_ = glm::vec3(
			sin(horizontalAngle_ - half_pi<float>()),
			0,
			cos(horizontalAngle_ - half_pi<float>())
			);

		up_ = glm::cross(right_, direction_);
	}


	Camera::~Camera()
	{
	}

}
