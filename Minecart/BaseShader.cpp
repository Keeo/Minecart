#include "stdafx.h"
#include "BaseShader.h"

namespace view
{

	BaseShader::BaseShader(std::string vertex, std::string fragment)
	{
		// http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/
		bool ret = shader_.loadFromFile(vertex, fragment);
		assert(ret);

		sf::Shader::bind(&shader_);
		glGetIntegerv(GL_CURRENT_PROGRAM, &shaderId_);
		assert(shaderId_ != -1);
		sf::Shader::bind(NULL);

		modelLoc_ = glGetUniformLocation(shaderId_, "model");
		viewLoc_ = glGetUniformLocation(shaderId_, "view");
		projectionLoc_ = glGetUniformLocation(shaderId_, "projection");

		assert(modelLoc_ != -1);
		assert(viewLoc_ != -1);
		assert(projectionLoc_ != -1);
	}

	void BaseShader::bind()
	{
		sf::Shader::bind(&shader_);

		CameraData cd;
		Post(EEvent::FetchCameraData, &cd, 0);
		assert(cd.position != NULL);
		assert(cd.projection != NULL);
		assert(cd.view != NULL);
		
		glUniformMatrix4fv(viewLoc_, 1, GL_FALSE, glm::value_ptr(*cd.view));
		glUniformMatrix4fv(projectionLoc_, 1, GL_FALSE, glm::value_ptr(*cd.projection));
	}

	void BaseShader::unbind()
	{
		sf::Shader::bind(NULL);
	}

	void BaseShader::loadModelMatrix(glm::mat4* model)
	{
		glUniformMatrix4fv(modelLoc_, 1, GL_FALSE, glm::value_ptr(*model));
	}

	BaseShader::~BaseShader()
	{
	}

}
