#include "Trophy.h"

#include "glad/glad.h"
#include "Shaders/EBO.h"
#include "Shaders/VAO.h"

GLuint trophyIndices[]
{

	0,1,2,
	0,2,4,
	0,4,3,
	0,3,1,
	5,1,2,
	5,2,4,
	5,4,3,
	5,3,1,

};
Trophy::Trophy()
{

}
void Trophy::CreateTrophy(glm::vec3 position, glm::vec3 size)
{
	std::vector<trophyVertex> trophy_vertices;
	trophy_vertices.push_back(trophyVertex{position.x + size.x/2,position.y,position.z+size.z/2,1.f,1.f,0.f });
	trophy_vertices.push_back(trophyVertex{ position.x,position.y+size.y/2,position.z,0.f,1.f,1.f });
	trophy_vertices.push_back(trophyVertex{ position.x+size.x,position.y + size.y / 2,position.z,0.f,1.f,1.f });
	trophy_vertices.push_back(trophyVertex{ position.x,position.y + size.y / 2,position.z+size.z,0.f,1.f,1.f });
	trophy_vertices.push_back(trophyVertex{ position.x+size.x,position.y + size.y / 2,position.z +size.z,0.f,1.f,1.f });
	trophy_vertices.push_back(trophyVertex{ position.x+size.x/2,position.y + size.y,position.z + size.z/2,1.f,0.f,1.f });
	DrawTrophy(trophy_vertices);
	AABB.Position = position;
	AABB.Extent = glm::vec3(size.x / 2, size.y / 2, size.z / 2);
}

void Trophy::DrawTrophy(std::vector<trophyVertex> points)
{
	//Draw Square
	VAO trophyVAO;
	trophyVAO.Bind();

	VBO trophyVBO(reinterpret_cast<GLfloat*>(points.data()), static_cast<GLsizeiptr>(points.size() * sizeof(trophyVertex)));
	trophyVBO.Bind();

	EBO trophyEBO(trophyIndices, sizeof(trophyIndices));
	trophyEBO.Bind();

	//Specify vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(trophyVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(trophyVertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, sizeof(trophyIndices), GL_UNSIGNED_INT, nullptr);

	trophyVAO.Unbind();
	trophyVBO.Unbind();
	trophyEBO.Unbind();

	trophyVAO.Delete();
	trophyVBO.Delete();
	trophyEBO.Delete();
}
