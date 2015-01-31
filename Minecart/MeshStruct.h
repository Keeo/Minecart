#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

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
		std::mutex meshBuilding;

		std::vector<glm::u8vec4>* g_vertex_buffer_data;
		std::vector<GLuint>* g_index_buffer_data;
		size_t quadcount = 0;

		GLuint vertexArrayID = -1;
		GLuint vertexBufferID = -1;
		GLuint indexBufferID = -1;

		bool meshReady = false;
		bool gpuReady = false;
		bool initDone = false;

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

		void init() {
			assert(!initDone);
			glGenVertexArrays(1, &vertexArrayID);
			assert(vertexArrayID != -1);

			glGenBuffers(1, &vertexBufferID);
			assert(vertexBufferID != -1);

			glGenBuffers(1, &indexBufferID);
			assert(indexBufferID != -1);


			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(
				0,
				4,
				GL_UNSIGNED_BYTE,
				GL_FALSE,
				4 * sizeof(GLubyte),
				(void*)0
				);
			glBindVertexArray(0);
			initDone = true;
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
			assert(initDone);
			assert(meshReady);
			assert(!gpuReady);
			std::lock_guard<std::mutex> lg(meshBuilding);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::u8vec4) * g_vertex_buffer_data->size(), g_vertex_buffer_data->data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * g_index_buffer_data->size(), g_index_buffer_data->data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			gpuReady = true;
			//deleteBuffers();
		}

		void reset()
		{
			std::lock_guard<std::mutex> lg(meshBuilding);
			if (g_vertex_buffer_data != NULL) {
				g_vertex_buffer_data->clear();
			}
			else {
				g_vertex_buffer_data = new std::vector<glm::u8vec4>();
			}

			if (g_index_buffer_data != NULL) {
				g_index_buffer_data->clear();
			}
			else {
				g_index_buffer_data = new std::vector<GLuint>();
			}

			meshReady = false;
			gpuReady = false;
		}

		~MeshStruct()
		{
			if (g_vertex_buffer_data != NULL) delete g_vertex_buffer_data;
			if (g_index_buffer_data != NULL) delete g_index_buffer_data;
			
			if (vertexArrayID != -1) glDeleteVertexArrays(1, &vertexArrayID);
			if (vertexBufferID != -1) glDeleteBuffers(1, &vertexBufferID);
			if (indexBufferID != -1) glDeleteBuffers(1, &indexBufferID);
		}

		void deleteBuffers()
		{
			std::lock_guard<std::mutex> lg(meshBuilding);
			delete g_vertex_buffer_data;
			delete g_index_buffer_data;

			g_vertex_buffer_data = NULL;
			g_index_buffer_data = NULL;
		}
	};

}
