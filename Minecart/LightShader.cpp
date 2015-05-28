#include "stdafx.h"
#include "LightShader.h"

namespace view
{

	LightShader::LightShader() : BaseShader("./shaders/light.vert", "./shaders/light.frag")
	{
		linStepBleedPos_ = glGetUniformLocation(shaderId_, "linStepBleed");
		maxVariancePos_ = glGetUniformLocation(shaderId_, "maxVariance");
		blurStepPos_ = glGetUniformLocation(shaderId_, "blurStep");
	}

	void LightShader::bind()
	{
		BaseShader::bind();

		CameraData light;
		Post(EEvent::FetchLightData, &light, 0);

		CameraData cd;
		Post(EEvent::FetchCameraData, &cd, 0);
		assert(cd.position != NULL);
		assert(cd.projection != NULL);
		assert(cd.view != NULL);

		glm::mat4 lightView = glm::lookAt(*light.position, *light.position - *light.direction, glm::vec3(0, 1, 0));
		glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 1.0f, 200.0f);
		glm::mat4 lightMat = depthProjectionMatrix * lightView;

		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
			);
		glm::mat4 lightMatBias = biasMatrix * lightMat;
		glUniformMatrix4fv(lightMatLoc_, 1, GL_FALSE, glm::value_ptr(lightMatBias));
		glUniform3fv(lightPositionLoc_, 1, glm::value_ptr(*light.position));

		configVals();

		glUniform1fv(linStepBleedPos_, 1, &linStepBleed_);
		glUniform1fv(maxVariancePos_, 1, &maxVariance_);
		glUniform1fv(blurStepPos_, 1, &blurStep_);
	}

	void LightShader::configVals()
	{
		using  namespace sf;

		if (Keyboard::isKeyPressed(Keyboard::Comma) && !Keyboard::isKeyPressed(Keyboard::RShift) && !Keyboard::isKeyPressed(Keyboard::LShift)) {
			linStepBleed_ += 0.005;
			linStepBleed_ = boost::algorithm::clamp(linStepBleed_, 0, 1);
			std::cout << "Lin Step Bleed: " << linStepBleed_ << std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Period) && !Keyboard::isKeyPressed(Keyboard::RShift) && !Keyboard::isKeyPressed(Keyboard::LShift)) {
			linStepBleed_ -= 0.005;
			linStepBleed_ = boost::algorithm::clamp(linStepBleed_, 0, 1);
			std::cout << "Lin Step Bleed: " << linStepBleed_ << std::endl;
		}


		if (Keyboard::isKeyPressed(Keyboard::Comma) && Keyboard::isKeyPressed(Keyboard::RShift) && !Keyboard::isKeyPressed(Keyboard::LShift)) {
			maxVariance_ += 0.0000005;
			maxVariance_ = boost::algorithm::clamp(maxVariance_, 0, 1);
			std::cout << "Max Variance: " << std::setprecision(15) << maxVariance_ << std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Period) && Keyboard::isKeyPressed(Keyboard::RShift) && !Keyboard::isKeyPressed(Keyboard::LShift)) {
			maxVariance_ -= 0.0000005;
			maxVariance_ = boost::algorithm::clamp(maxVariance_, 0, 1);
			std::cout << "Max Variance: " << std::setprecision(15) << maxVariance_ << std::endl;
		}

		if (Keyboard::isKeyPressed(Keyboard::Comma) && !Keyboard::isKeyPressed(Keyboard::RShift) && Keyboard::isKeyPressed(Keyboard::LShift)) {
			blurStep_ += 0.005;
			std::cout << "Blur step: " << blurStep_ << std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Period) && !Keyboard::isKeyPressed(Keyboard::RShift) && Keyboard::isKeyPressed(Keyboard::LShift)) {
			blurStep_ -= 0.005;
			std::cout << "Blur step: " << blurStep_ << std::endl;
		}
	}

	LightShader::~LightShader()
	{
	}

}
