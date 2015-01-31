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

	struct MeshStruct
	{
		std::vector<glm::u8vec4>* g_vertex_buffer_data;
		std::vector<GLuint>* g_index_buffer_data;
		size_t quadcount = 0;

		GLuint vertexArrayID = -1;
		GLuint vertexBufferID = -1;
		GLuint indexBufferID = -1;

		bool renderReady = false;
		bool meshReady = false;
		bool vaoReady = false;
		bool initReady = false;

		MeshStruct() : g_vertex_buffer_data(new std::vector<glm::u8vec4>()), g_index_buffer_data(new std::vector<GLuint>())
		{

		}

		void draw()
		{
			glBindVertexArray(vertexArrayID);
			GLuint rendertype = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ? GL_LINES : GL_TRIANGLES;
			glDrawElements(rendertype, static_cast<GLsizei>(6 * quadcount), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		void newOrder()
		{
			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);
			
			glGenBuffers(1, &vertexBufferID);
			glGenBuffers(1, &indexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);


			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::u8vec4) * g_vertex_buffer_data->size(), g_vertex_buffer_data->data(), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * g_index_buffer_data->size(), g_index_buffer_data->data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_UNSIGNED_BYTE, GL_FALSE, 4 * sizeof(GLubyte), (void*)0);

			glBindVertexArray(0);

			deleteBuffers();
		}

		void init() {
			glGenVertexArrays(1, &vertexArrayID);
			assert(vertexArrayID != -1);

			glGenBuffers(1, &vertexBufferID);
			assert(vertexBufferID != -1);

			glGenBuffers(1, &indexBufferID);
			assert(indexBufferID != -1);
		}

		void bind()
		{
			glBindVertexArray(vertexArrayID);
		}

		void unbind()
		{
			glBindVertexArray(0);
		}

		void moveToGpu() {
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::u8vec4) * g_vertex_buffer_data->size(), g_vertex_buffer_data->data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * g_index_buffer_data->size(), g_index_buffer_data->data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			deleteBuffers();
		}

		void makeVAO()
		{
			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

			glEnableVertexAttribArray(0);
			//glEnableVertexAttribArray(5);
			glVertexAttribPointer(
				0,
				4,
				GL_UNSIGNED_BYTE,
				GL_FALSE,
				4 * sizeof(GLubyte),
				(void*)0
				);

			/*glVertexAttribPointer(
				5,                 // attribute
				3,                 // number of elements per vertex
				GL_FLOAT,          // the type of each element
				GL_FALSE,          // take our values as-is
				4 * sizeof(GLfloat),// no extra data between each position
				(GLvoid*)(3 * sizeof(GLfloat))// offset of first element
				);*/
			glBindVertexArray(0);
		}

		~MeshStruct()
		{
			sf::Clock c;
			if (g_vertex_buffer_data != NULL) delete g_vertex_buffer_data;
			if (g_index_buffer_data != NULL) delete g_index_buffer_data;
			
			if (vertexArrayID != -1) glDeleteVertexArrays(1, &vertexArrayID);
			if (vertexBufferID != -1) glDeleteBuffers(1, &vertexBufferID);
			if (indexBufferID != -1) glDeleteBuffers(1, &indexBufferID);
			std::cout << "Mesh deleted in:" << std::setprecision(10) << c.getElapsedTime().asSeconds() << std::endl;
		}

		void deleteBuffers()
		{
			delete g_vertex_buffer_data;
			delete g_index_buffer_data;

			g_vertex_buffer_data = NULL;
			g_index_buffer_data = NULL;
		}
	};

}
