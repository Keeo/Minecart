#pragma once

#include <memory>

#include "MeshStruct.h"

namespace view {

	class Drawable
	{
		std::shared_ptr<view::MeshStruct> mesh_ = NULL;
	public:
		std::shared_ptr<view::MeshStruct> getMesh() { return mesh_; }
		void setMesh(std::shared_ptr<view::MeshStruct> mesh) { mesh_ = mesh; }
	};

}
