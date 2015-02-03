#pragma once

namespace model
{

	class TripleChunkBuffer;

	class CubeFinder
	{
		TripleChunkBuffer* tcb_;
	public:
		CubeFinder(TripleChunkBuffer* tcb);
		~CubeFinder();

		glm::i32vec3 findCube(const glm::vec3& pos,const glm::vec3& dir, int maxLength = 100);
	};

}
