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

namespace view {

	struct MeshStruct
	{
		std::vector<GLfloat> g_vertex_buffer_data;
		GLuint vertexArrayID = -1;
		GLuint vertexBufferID = -1;
		glm::mat4 model;

		void print()
		{
			std::cout << "VBDPrint: ";
			for (int i = 0; i < std::min(g_vertex_buffer_data.size(), (std::size_t)20); ++i)
				std::cout << g_vertex_buffer_data[i] << ' ';
			std::cout << "__end" << std::endl;
		}

		void pushNormal(EDirection d)
		{
			float x, y, z;
			switch (d) {
			case UP:
				x = 0;
				y = 1;
				z = 0;
				break;

			case DOWN:
				x = 0;
				y = -1;
				z = 0;
				break;

			case LEFT:
				x = -1;
				y = 0;
				z = 0;
				break;

			case RIGHT:
				x = 1;
				y = 0;
				z = 0;
				break;

			case FORWARD:
				x = 0;
				y = 0;
				z = -1;
				break;

			case BACKWARD:
				x = 0;
				y = 0;
				z = 1;
				break;
			}

			g_vertex_buffer_data.push_back(x);
			g_vertex_buffer_data.push_back(y);
			g_vertex_buffer_data.push_back(z);
		}

		void init() {
			glGenVertexArrays(1, &vertexArrayID);
			assert(vertexArrayID != -1);

			glGenBuffers(1, &vertexBufferID);
			assert(vertexBufferID != -1);
		}

		void moveToGpu() {
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * g_vertex_buffer_data.size(), g_vertex_buffer_data.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				8 * sizeof(GLfloat),
				(void*)0
				);

			glVertexAttribPointer(
				1,                 // attribute
				2,                 // number of elements per vertex
				GL_FLOAT,          // the type of each element
				GL_FALSE,          // take our values as-is
				8 * sizeof(GLfloat),// no extra data between each position
				(GLvoid*)(3 * sizeof(GLfloat))// offset of first element
				);

			glVertexAttribPointer(
				5,                 // attribute
				3,                 // number of elements per vertex
				GL_FLOAT,          // the type of each element
				GL_FALSE,          // take our values as-is
				8 * sizeof(GLfloat),// no extra data between each position
				(GLvoid*)(5 * sizeof(GLfloat))// offset of first element
				);
			glBindVertexArray(0);
		}

		~MeshStruct() {
			glDeleteBuffers(1, &vertexBufferID);
			glDeleteVertexArrays(1, &vertexArrayID);
		}
	};

}
