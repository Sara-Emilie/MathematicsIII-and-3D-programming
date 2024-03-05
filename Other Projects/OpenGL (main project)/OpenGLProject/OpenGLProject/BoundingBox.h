#pragma once
#include "glm/glm.hpp"
#include <stdlib.h> 


class BoundingBox
{
	public:
	glm::vec3 Extent;
	glm::vec3 Position;
	
	BoundingBox();

	bool TestAABBAABB(BoundingBox b)
	{
		auto a = *this;

		if (abs(a.Position[0] - b.Position[0]) > (a.Extent[0] + b.Extent[0])) return false;
		if (abs(a.Position[1] - b.Position[1]) > (a.Extent[1] + b.Extent[1])) return false;
		if (abs(a.Position[2] - b.Position[2]) > (a.Extent[2] + b.Extent[2])) return false;
		return true;
	}

};

