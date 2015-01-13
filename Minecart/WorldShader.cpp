#include "stdafx.h"
#include "WorldShader.h"

namespace view
{
	WorldShader::WorldShader()
	{
		// http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/
		bool ret = shader_.loadFromFile("./shaders/world.vert", "./shaders/world.frag");
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

		img_.loadFromFile("./textures/cubes.png");
		tex_.loadFromImage(img_);
		shader_.setParameter("sampler", tex_);
	}

	void WorldShader::loadModelMatrix(glm::mat4* model)
	{
		glUniformMatrix4fv(modelLoc_, 1, GL_FALSE, glm::value_ptr(*model));
	}

	void WorldShader::bind()
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

	void WorldShader::unbind()
	{
		sf::Shader::bind(NULL);
	}

	WorldShader::~WorldShader()
	{
	}

}
