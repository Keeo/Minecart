#pragma once

#include <gl/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Constants.h"
#include "GameTime.h"
#include "IEventMessagingSystem.h"

namespace view {

	struct CameraData {
		glm::mat4* projection = NULL;
		glm::mat4* view = NULL;
		glm::vec3* position = NULL;
	};

	class Camera : model::IEventMessagingSystem
	{
	public:
		Camera();
		Camera(const Camera& orig);
		virtual ~Camera();

		void init();
		void update(const GameTime&);
		void draw(void* data);
		void drawWeather(void* data);

		void getCameraData(void* data);

	private:
		glm::mat4 projection_;
		glm::mat4 view_;

		glm::vec3 position_;
		glm::vec3 positionLast_;

		glm::vec3 direction_;
		glm::vec3 right_;
		glm::vec3 up_;

		float horizontalAngle_ = 0;
		float verticalAngle_ = 0;

		void rotate(float&);
		void move(float&);
		void updateDirection();

		glm::i32vec3& posToChunk(glm::vec3& const pos);

		void getPositionPointer(void* data);
	};

}

