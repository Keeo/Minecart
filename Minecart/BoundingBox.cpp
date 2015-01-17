#include "stdafx.h"
#include "BoundingBox.h"

namespace view
{

	BoundingBox::BoundingBox()
	{
		mesh_ = std::make_shared<MeshStruct>();
		mesh_->init();
		moveToGpu();
		makeVAO();
	}

	void BoundingBox::makeVAO()
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
			6 * sizeof(GLfloat),
			(void*)0
			);

		glBindVertexArray(0);
	}

	void BoundingBox::moveToGpu()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh_->vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh_->g_vertex_buffer_data.size(), mesh_->g_vertex_buffer_data.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_->indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*mesh_->g_index_buffer_data.size(), mesh_->g_index_buffer_data.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	BoundingBox::~BoundingBox()
	{
	}


	GLfloat BoundingBox::boundingVertexData[] = {
		//  X                           Y                           Z 
		// face 0:
		Constants::CHUNK_SIZE, Constants::CHUNK_SIZE, Constants::CHUNK_SIZE,
		0, Constants::CHUNK_SIZE, Constants::CHUNK_SIZE,
		Constants::CHUNK_SIZE, 0, Constants::CHUNK_SIZE,
		0, 0, Constants::CHUNK_SIZE,

		// face 1:
		Constants::CHUNK_SIZE, Constants::CHUNK_SIZE, Constants::CHUNK_SIZE,
		Constants::CHUNK_SIZE, 0, Constants::CHUNK_SIZE,
		Constants::CHUNK_SIZE, Constants::CHUNK_SIZE, 0,
		Constants::CHUNK_SIZE, 0, 0,

		// face 2:
		Constants::CHUNK_SIZE, Constants::CHUNK_SIZE, Constants::CHUNK_SIZE,
		Constants::CHUNK_SIZE, Constants::CHUNK_SIZE, 0,
		0, Constants::CHUNK_SIZE, Constants::CHUNK_SIZE,
		0, Constants::CHUNK_SIZE, 0,

		// face 3:
		Constants::CHUNK_SIZE, Constants::CHUNK_SIZE, 0,
		Constants::CHUNK_SIZE, 0, 0,
		0, Constants::CHUNK_SIZE, 0,
		0, 0, 0,

		// face 4:
		0, Constants::CHUNK_SIZE, Constants::CHUNK_SIZE,
		0, Constants::CHUNK_SIZE, 0,
		0, 0, Constants::CHUNK_SIZE,
		0, 0, 0,

		// face 5:
		Constants::CHUNK_SIZE, 0, Constants::CHUNK_SIZE,
		0, 0, Constants::CHUNK_SIZE,
		Constants::CHUNK_SIZE, 0, 0,
		0, 0, 0,
	};

	GLuint BoundingBox::boundingIndexData[] = {
		0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7, 8, 9, 10, 10, 9, 11,
		12, 13, 14, 14, 13, 15, 16, 17, 18, 18, 17, 19, 20, 21, 22, 22, 21, 23,
	};
}
