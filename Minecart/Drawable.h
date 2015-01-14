#pragma once

#include <memory>

#include "MeshStruct.h"
#include "MeshStructB.h"

namespace view {

	class Drawable
	{
		std::shared_ptr<view::MeshStruct> mesh_ = NULL;
		std::shared_ptr<view::MeshStructB> meshB_ = NULL;

	public:
		std::shared_ptr<view::MeshStruct> getMesh() { return mesh_; }
		void setMesh(std::shared_ptr<view::MeshStruct> mesh) { mesh_ = mesh; }

		std::shared_ptr<view::MeshStructB> getMeshB() { return meshB_; }
		void setMeshB(std::shared_ptr<view::MeshStructB> meshb) { meshB_ = meshb; }
	};

}
