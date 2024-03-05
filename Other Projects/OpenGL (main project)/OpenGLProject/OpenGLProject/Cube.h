#pragma once
#include "vector"
#include "Shaders/VAO.h"
#include "Shaders/VBO.h"
#include "Shaders/EBO.h"
#include "Shaders/ShaderClass.h"
#include <glm/glm.hpp>

#ifndef CUBE_H
#define CUBE_H

struct CubeVertex
{
	float x, y, z;
	float r, g, b;
	float u, v;
};


class Cube
{
	public:

	Cube();
	void DrawCube(std::vector<CubeVertex> points);
	void CreateCube(glm::vec3 position, float scale, float rotation);
};

#endif // CUBE_H