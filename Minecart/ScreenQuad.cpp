#include "stdafx.h"
#include "ScreenQuad.h"

namespace view
{
	ScreenQuad::ScreenQuad()
	{
		mesh_ = std::make_shared<MeshStruct>();
		mesh_->init();
		moveToGpu();
		makeVAO();
	}

	void ScreenQuad::draw(bool triangles)
	{
		mesh_->bind();
		glDrawElements(triangles ? GL_TRIANGLES : GL_LINES, 6, GL_UNSIGNED_INT, 0);
		mesh_->unbind();
	}

	void ScreenQuad::makeVAO()
	{
		glBindVertexArray(mesh_->vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, mesh_->vertexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_->indexBufferID);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0 * sizeof(GLfloat),
			(void*)0
			);

		glBindVertexArray(0);
	}

	void ScreenQuad::moveToGpu()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh_->vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, &quadVertexData[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_->indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, &quadIndexData[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	ScreenQuad::~ScreenQuad()
	{
	}


	GLfloat ScreenQuad::quadVertexData[] = {
		 1, 1, 0,
		-1, 1, 0,
		 1, -1, 0,
		-1, -1, 0,
	};

	GLuint ScreenQuad::quadIndexData[] = {
		0, 1, 2, 2, 1, 3,
	};

}
