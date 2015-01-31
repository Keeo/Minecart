#pragma once

#include <memory>
#include <atomic>

#include "MeshStruct.h"

namespace view {

	class Drawable
	{
	protected:
		std::shared_ptr<view::MeshStruct> mesh_ = NULL;

	public:

		std::atomic<bool> readyRender = false;

		glm::mat4 model;

		void Drawable::reset()
		{
			readyRender = false;
			if (mesh_ != NULL) {
				mesh_->reset();
			}
		}

		std::shared_ptr<view::MeshStruct> getMesh()
		{
			return mesh_;
		}

		void setMesh(std::shared_ptr<view::MeshStruct> mesh)
		{
			mesh_ = mesh;
			readyRender = true;
		}

		virtual ~Drawable()
		{
		}
	};

}
