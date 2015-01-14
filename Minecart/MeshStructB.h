#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include <gl/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EDirection.h"

namespace view
{

	struct MeshStructB
	{
		std::vector<glm::vec3> g_vertex_buffer_data;
		std::vector<GLuint> g_index_buffer_data;

		GLuint vertexArrayID = -1;
		GLuint vertexBufferID = -1;
		GLuint indexBufferID = -1;

		glm::mat4 model;
		
		void init() {
			glGenVertexArrays(1, &vertexArrayID);
			assert(vertexArrayID != -1);

			glGenBuffers(1, &vertexBufferID);
			assert(vertexBufferID != -1);

			glGenBuffers(1, &indexBufferID);
			assert(indexBufferID != -1);
		}

		int getQuadcount()
		{
			return g_vertex_buffer_data.size() / 8;
		}

		void moveToGpu() {
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * g_vertex_buffer_data.size(), g_vertex_buffer_data.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*g_index_buffer_data.size(), g_index_buffer_data.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				6 * sizeof(GLfloat),
				(void*)0
				);

			glVertexAttribPointer(
				5,                 // attribute
				3,                 // number of elements per vertex
				GL_FLOAT,          // the type of each element
				GL_FALSE,          // take our values as-is
				6 * sizeof(GLfloat),// no extra data between each position
				(GLvoid*)(3 * sizeof(GLfloat))// offset of first element
				);
			glBindVertexArray(0);
		}

		~MeshStructB() {
			glDeleteBuffers(1, &vertexBufferID);
			glDeleteBuffers(1, &indexBufferID);
			glDeleteVertexArrays(1, &vertexArrayID);
		}
	};

}
