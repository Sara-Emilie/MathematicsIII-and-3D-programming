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

void Wall::CreateXWall(glm::vec3 position, glm::vec3 offset, glm::vec3 Color0, glm::vec3 Color1)
{
	std::vector<WallVertex> points;
	points.push_back(WallVertex{ position.x,position.y,position.z, Color0.x,Color0.y,Color0.z });
	points.push_back(WallVertex{ position.x + offset.x,position.y,position.z,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x,position.y + offset.y,position.z ,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x + offset.x,position.y + offset.y,position.z,Color0.x,Color0.y,Color0.z });
	
	DrawSquare(points);
	
}

void Wall::CreateYWall(glm::vec3 position, glm::vec3 offset, glm::vec3 Color0, glm::vec3 Color1)
{
	std::vector<WallVertex> points;
	points.push_back(WallVertex{ position.x,position.y,position.z ,Color0.x,Color0.y,Color0.z });
	points.push_back(WallVertex{ position.x ,position.y,position.z + offset.z ,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x + offset.x,position.y,position.z,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x + offset.x,position.y,position.z + offset.z,Color0.x,Color0.y,Color0.z });
	
	DrawSquare(points);
	
}
void Wall::CreateZWall(glm::vec3 position, glm::vec3 offset, glm::vec3 Color0, glm::vec3 Color1)
{
	std::vector<WallVertex> points;
	points.push_back(WallVertex{ position.x,position.y,position.z ,Color0.x,Color0.y,Color0.z });
	points.push_back(WallVertex{ position.x ,position.y,position.z + offset.z,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x ,position.y + offset.y,position.z ,Color1.x,Color1.y,Color1.z });
	points.push_back(WallVertex{ position.x ,position.y + offset.y,position.z + offset.z,Color0.x,Color0.y,Color0.z });

	DrawSquare(points);
	

}
void Wall::CreateHouse(glm::vec3 position, glm::vec3 offset)
{
	// Define the dimensions of the door
	float doorWidth = 0.4f; // Width of the door
	float doorHeight = 0.6f; // Height of the door

	// Define the position of the door
	glm::vec3 doorPosition =glm::vec3( position.x + doorWidth,position.y,position.z);

	// Define the dimensions of the house
	float houseWidth = doorWidth * 5; // Width of the house
	float houseHeight = doorHeight + doorHeight / 1; // Height of the house

	//Colors
	//glm::vec3 WallColor = glm::vec3(0.2f, 0.3f, 0.2f);
	glm::vec3 WallColor1 = glm::vec3(0.2f, 0.31f, 0.2f);
	glm::vec3 DoorColor = glm::vec3(0.6f, 0.3f, 0.1f);
	glm::vec3 DoorColor1 = glm::vec3(0.61f, 0.31f, 0.11f);

	//floor
	CreateYWall(glm::vec3(-10, 0, -10),glm::vec3( 20,20, 20), glm::vec3(0, 0.8f, 0.2f), glm::vec3(0, 0.2f, 0));

		//Door
	
	CreateXWall(glm::vec3(doorPosition.x , doorPosition.y , doorPosition.z ),glm::vec3(doorWidth, doorHeight, 1), DoorColor, DoorColor1);

		//House around door
	CreateXWall(glm::vec3(doorPosition.x + doorWidth, doorPosition.y, doorPosition.z), glm::vec3(houseWidth / 2, houseHeight, 0.1f), WallColor, WallColor1);
	CreateXWall(glm::vec3(doorPosition.x - (houseWidth / 2) , doorPosition.y, doorPosition.z), glm::vec3(houseWidth / 2, houseHeight, 1), WallColor, WallColor1);

	CreateZWall(glm::vec3(doorPosition.x - (houseWidth / 2), doorPosition.y, doorPosition.z - houseWidth), glm::vec3(1, houseHeight, houseWidth), WallColor, WallColor1);
	CreateZWall(glm::vec3(doorPosition.x + (houseWidth / 2) + doorWidth, doorPosition.y, doorPosition.z - houseWidth), glm::vec3(1, houseHeight, houseWidth), WallColor, WallColor);

	CreateXWall(glm::vec3(doorPosition.x - (houseWidth / 2), doorPosition.y, doorPosition.z - houseWidth), glm::vec3(houseWidth + doorWidth, houseHeight, 1), WallColor, WallColor1);
	CreateXWall(glm::vec3(doorPosition.x, doorPosition.y + doorHeight, doorPosition.z), glm::vec3(doorWidth, houseHeight - doorHeight, 1), WallColor, WallColor1);
	//Roof
	CreateYWall(glm::vec3(doorPosition.x - (houseWidth / 2), doorPosition.y + houseHeight, doorPosition.z - houseWidth), glm::vec3(houseWidth + doorWidth, 1,houseWidth), WallColor, WallColor1);

	AABB.Position = glm::vec3(position.x,position.y,position.z );
	AABB.Extent = glm::vec3(offset.x/2,offset.y/2,offset.z/2);
}



