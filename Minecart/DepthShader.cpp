#include "stdafx.h"
#include "DepthShader.h"

namespace view
{

	DepthShader::DepthShader() : BaseShader("./shaders/depth_texture.vert", "./shaders/depth_texture.frag")
	{
	}

	void DepthShader::bind()
	{
		sf::Shader::bind(&shader_);

		CameraData light;
		Post(EEvent::FetchLightData, &light, 0);
		glUniform3fv(camPositionLoc_, 1, glm::value_ptr(*light.position));

		CameraData cd;
		Post(EEvent::FetchCameraData, &cd, 0);
		assert(cd.position != NULL);
		assert(cd.projection != NULL);
		assert(cd.view != NULL);

		glm::mat4 lightView = glm::lookAt(*light.position, *light.position - *light.direction, glm::vec3(0, 1, 0));
		glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 1.0f, 200.0f);
		glm::mat4 lightMat = depthProjectionMatrix * lightView;

		glUniformMatrix4fv(viewLoc_, 1, GL_FALSE, glm::value_ptr(lightView));
		glUniformMatrix4fv(projectionLoc_, 1, GL_FALSE, glm::value_ptr(depthProjectionMatrix));

		glUniformMatrix4fv(lightMatLoc_, 1, GL_FALSE, glm::value_ptr(lightMat));
		glUniform3fv(lightPositionLoc_, 1, glm::value_ptr(*light.position));
	}

	DepthShader::~DepthShader()
	{
	}

}
