#pragma once
#include <vector>

#include "glm/vec3.hpp"

struct trophyVertex
{
	float x, y, z, r, g, b;
};
class Trophy
{
public:
	Trophy();
	void CreateTrophy(glm::vec3 position, glm::vec3 size);
	void DrawTrophy(std::vector<trophyVertex> points);
};

