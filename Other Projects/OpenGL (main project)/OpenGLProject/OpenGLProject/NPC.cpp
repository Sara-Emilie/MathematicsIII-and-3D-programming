#include "NPC.h"

#include <vector>

#include "Shaders/EBO.h"
#include "Shaders/VAO.h"

GLuint NPCIndices[]
{
	0,1,2,
	0,2,3,
	3,4,2,
	4,2,1
};

NPC::NPC()
{
	
}

void NPC::Movement(glm::vec3 position, glm::vec3 Targetlocation)
{
	
}

void NPC::CreateNPC(glm::vec3 position, glm::vec3 size)
{
	

	std::vector<NPCVertex> NPCPoints;
	NPCPoints.push_back(NPCVertex{ position.x,position.y,position.z ,1.f,0.f,0.f});
	NPCPoints.push_back(NPCVertex{ position.x + size.x,position.y,position.z,1.f,0.f,0.f });
	NPCPoints.push_back(NPCVertex{ position.x+size.x/2,position.y+size.y,position.z+size.z/2,1.f,0.f,0.f });
	NPCPoints.push_back(NPCVertex{ position.x,position.y,position.z + size.z,1.f,0.f,0.f });
	NPCPoints.push_back(NPCVertex{ position.x + size.x,position.y,position.z + size.z,1.f,0.f,0.f });
	DrawNPC(NPCPoints);

}



void NPC::DrawNPC(std::vector<NPCVertex> points)
{
	//Draw Square
	VAO NPCVAO;
	NPCVAO.Bind();

	VBO NPCVBO(reinterpret_cast<GLfloat*>(points.data()), static_cast<GLsizeiptr>(points.size() * sizeof(NPCVertex)));
	NPCVBO.Bind();

	EBO NPCEBO(NPCIndices, sizeof(NPCIndices));
	NPCEBO.Bind();

	//Specify vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(NPCVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(NPCVertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glDrawElements(GL_TRIANGLES, sizeof(NPCIndices), GL_UNSIGNED_INT, nullptr);

	NPCVAO.Unbind();
	NPCVBO.Unbind();
	NPCEBO.Unbind();

	NPCVAO.Delete();
	NPCVBO.Delete();
	NPCEBO.Delete();
}

void NPC::UpdateMovement(glm::vec3 position, glm::vec3 Targetlocation)
{
}
