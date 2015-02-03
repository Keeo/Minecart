#include "stdafx.h"
#include "CubeFinder.h"
#include "TripleChunkBuffer.h"


namespace model
{

	CubeFinder::CubeFinder(TripleChunkBuffer* tcb) : tcb_(tcb)
	{
	}

	glm::i32vec3 CubeFinder::findCube(const glm::vec3& pos, const glm::vec3& dir, int maxLength)
	{
		const glm::vec3 ndir(glm::normalize(dir));

		const glm::i32vec3 step(utils::Utils::sgn(ndir));

		glm::vec3 temp;
		temp.x = dir.x > 0 ? ceil(pos.x) : floor(pos.x);
		temp.y = dir.y > 0 ? ceil(pos.y) : floor(pos.y);
		temp.z = dir.z > 0 ? ceil(pos.z) : floor(pos.z);

		glm::vec3 tMax;
		tMax.x = (temp.x - pos.x) / ndir.x;
		tMax.y = (temp.y - pos.y) / ndir.y;
		tMax.z = (temp.z - pos.z) / ndir.z;

		glm::vec3 tDelta;
		tDelta.x = abs(1 / ndir.x);
		tDelta.y = abs(1 / ndir.y);
		tDelta.z = abs(1 / ndir.z);

		int x = (int)(pos.x);
		int y = (int)(pos.y);
		int z = (int)(pos.z);

		for (int i = 0; i<maxLength; ++i) {
			if (tMax.x < tMax.y) {
				if (tMax.x < tMax.z) {
					x = x + step.x;
					tMax.x = tMax.x + tDelta.x;
				}
				else {
					z = z + step.z;
					tMax.z = tMax.z + tDelta.z;
				}
			}
			else {
				if (tMax.y < tMax.z) {
					y = y + step.y;
					tMax.y = tMax.y + tDelta.y;
				}
				else {
					z = z + step.z;
					tMax.z = tMax.z + tDelta.z;
				}
			}
			glm::i32vec3 test(x, y, z);
			if (tcb_->getCube(test) != ECube::Air) {
				return test;
			}
		};
		return glm::i32vec3(0);
	}

	CubeFinder::~CubeFinder()
	{
	}

}
