#include "Wall.h"


unsigned int SquareIndices[] =
{
	0,1,2,
	3,1,2
};



Wall::Wall()
{


}
void Wall::DrawSquare(std::vector<WallVertex> position)
{


	//Draw Square
	VAO SquareVAO;
	SquareVAO.Bind();

	VBO SquareVBO(reinterpret_cast<GLfloat*>(position.data()), static_cast<GLsizeiptr>(position.size() * sizeof(WallVertex)));
	SquareVBO.Bind();

	EBO SquareEBO(SquareIndices, sizeof(SquareIndices));
	SquareEBO.Bind();

	//Specify vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(WallVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(WallVertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	SquareVAO.Unbind();
	SquareVBO.Unbind();
	SquareEBO.Unbind();

	SquareVAO.Delete();
	SquareVBO.Delete();
	SquareEBO.Delete();

}

void Wall::CreateXWall(glm::vec3 position, float xoffset, float yoffset, glm::vec3 Color0, glm::vec3 Color1)
{
	std::vector<WallVertex> points;
	points.push_back(WallVertex{ position.x,position.y,position.z, Color0.x,Color0.y,Color0.z });
	points.push_back(WallVertex{ position.x + xoffset,position.y,position.z,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x,position.y + yoffset,position.z ,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x + xoffset,position.y + yoffset,position.z,Color0.x,Color0.y,Color0.z });
	DrawSquare(points);
}

void Wall::CreateYWall(glm::vec3 position, float xoffset, float zoffset, glm::vec3 Color0, glm::vec3 Color1)
{
	std::vector<WallVertex> points;
	points.push_back(WallVertex{ position.x,position.y,position.z ,Color0.x,Color0.y,Color0.z });
	points.push_back(WallVertex{ position.x ,position.y,position.z + zoffset ,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x + xoffset,position.y,position.z,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x + xoffset,position.y,position.z + zoffset,Color0.x,Color0.y,Color0.z });
	DrawSquare(points);
}

void Wall::CreateZWall(glm::vec3 position, float yoffset, float zoffset, glm::vec3 Color0, glm::vec3 Color1)
{
	std::vector<WallVertex> points;
	points.push_back(WallVertex{ position.x,position.y,position.z ,Color0.x,Color0.y,Color0.z });
	points.push_back(WallVertex{ position.x ,position.y,position.z + zoffset,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x ,position.y + yoffset,position.z ,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x ,position.y + yoffset,position.z + zoffset,Color0.x,Color0.y,Color0.z });
	DrawSquare(points);

}



