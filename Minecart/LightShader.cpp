#include "stdafx.h"
#include "LightShader.h"

namespace view
{

	LightShader::LightShader() : BaseShader("./shaders/light.vert", "./shaders/light.frag")
	{
	}

	void LightShader::bind()
	{
		BaseShader::bind();

		glm::vec3 light;
		Post(EEvent::FetchLightData, &light, 0);

		CameraData cd;
		Post(EEvent::FetchCameraData, &cd, 0);
		assert(cd.position != NULL);
		assert(cd.projection != NULL);
		assert(cd.view != NULL);

		glm::mat4 lightView = glm::lookAt(light, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		glm::mat4 depthProjectionMatrix = glm::perspective<float>(90.0f, 1.0f, 1.0f, 500.0f);
		//glm::mat4 depthProjectionMatrix = glm::ortho<float>(-100, 100, -100, 100, -100, 200);
		glm::mat4 lightMat = depthProjectionMatrix * lightView;

		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
			);
		glm::mat4 lightMatBias = biasMatrix * lightMat;
		glUniformMatrix4fv(lightMatLoc_, 1, GL_FALSE, glm::value_ptr(lightMatBias));
		glUniform3fv(lightPositionLoc_, 1, glm::value_ptr(light));
	}

	LightShader::~LightShader()
	{
	}

}
