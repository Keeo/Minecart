//----------------------------------------------------------------------------------------
/**
* \file       Camera.h
* \author     Martin Moravek
* \date       2015/05/30
* \brief      Class that holds Camera data and its behaviour.
*/
//----------------------------------------------------------------------------------------
#pragma once


#include <gl/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <boost/algorithm/clamp.hpp>
#include <boost/math/constants/constants.hpp>

#include "Constants.h"
#include "GameTime.h"
#include "IEventMessagingSystem.h"

namespace view {

	struct CameraData {
		const glm::mat4* projection = NULL;
		const glm::mat4* view = NULL;
		const glm::vec3* position = NULL;
		const glm::vec3* direction = NULL;
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

		float horizontalAngle_;
		float verticalAngle_;

		void rotate(float&);
		void move(float&);
		void updateDirection();

		glm::i32vec3 posToChunk(const glm::vec3& pos);

		void getPositionPointer(void* data);
	};

}

