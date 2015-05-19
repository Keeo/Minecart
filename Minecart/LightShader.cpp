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

		glm::mat4 lightView = glm::lookAt(light, *cd.direction, glm::vec3(0, 1, 0));

		glm::mat4 lightMat = *cd.projection * lightView;
		glUniformMatrix4fv(lightMatLoc_, 1, GL_FALSE, glm::value_ptr(lightMat));
		glUniform3fv(lightPositionLoc_, 1, glm::value_ptr(light));
	}

	LightShader::~LightShader()
	{
	}

}
