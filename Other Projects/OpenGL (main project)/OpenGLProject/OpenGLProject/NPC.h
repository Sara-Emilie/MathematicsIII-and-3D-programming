#pragma once
#include <vector>

#include "glm/vec3.hpp"
struct NPCVertex
{
	float x, y, z, r, g, b;
};
class NPC
{

public:
	NPC();
	void Movement(glm::vec3 position, glm::vec3 Targetlocation);
	void CreateNPC(glm::vec3 position, glm::vec3 size);
	void DrawNPC(std::vector<NPCVertex> points);
	void UpdateMovement(glm::vec3 position, glm::vec3 Targetlocation);
};

