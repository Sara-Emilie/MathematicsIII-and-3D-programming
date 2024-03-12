#pragma once
#include <vector>
#include "Shaders/VAO.h"
#include "Shaders/VBO.h"
#include "Shaders/EBO.h"
#include "Shaders/ShaderClass.h"
#include <glm/glm.hpp>
#include "BoundingBox.h"

#ifndef WALL_H
#define WALL_H

struct WallVertex
{
	float x, y, z;
	float r, g, b;
	
};


class Wall
{
public:
	Wall();

	glm::vec3 WallColor;
	glm::vec3 WallColor1 ;
	glm::vec3 DoorColor;
	glm::vec3 DoorColor1;
	BoundingBox AABB;
	void DrawSquare(std::vector<WallVertex> position);
	void CreateXWall(glm::vec3 position, glm::vec3 offset, glm::vec3 Color0, glm::vec3 Color1);
	void CreateYWall(glm::vec3 position, glm::vec3 offset, glm::vec3 Color0, glm::vec3 Color1);
	void CreateZWall(glm::vec3 position, glm::vec3 offset, glm::vec3 Color0, glm::vec3 Color1);
	void CreateHouse(glm::vec3 position, glm::vec3 offset);
};	
#endif // WALL_H
