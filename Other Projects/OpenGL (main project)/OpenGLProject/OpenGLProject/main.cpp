#include <iostream>
#include <fstream>
#include <iomanip>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <cstddef>
#include <string>
#include "NPC.h"
#include <Eigen/Dense>
#include "Trophy.h"
#include "Shaders/ShaderClass.h"
#include "Shaders/VAO.h"
#include "Shaders/VBO.h"
#include "Shaders/EBO.h"
#include "Camera.h"
#include "Cube.h"
#include "Wall.h"
using namespace std;
using namespace Eigen;
using namespace glm;

// Window dimensions
const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "OpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLProject", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, width, height);

	

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	//// Define the dimensions of the door
	//float doorWidth = 0.4f; // Width of the door
	//float doorHeight = 0.6f; // Height of the door

	//// Define the position of the door
	//glm::vec3 doorPosition = glm::vec3(-2.0f, 0.0f, -1.0f);

	//// Define the dimensions of the house
	//float houseWidth = doorWidth * 5; // Width of the house
	//float houseHeight = doorHeight + doorHeight / 1; // Height of the house

	//	//Colors
	//glm::vec3 WallColor = glm::vec3(0.2f, 0.3f, 0.2f);
	//glm::vec3 WallColor1 = glm::vec3(0.2f, 0.31f, 0.2f);
	//glm::vec3 DoorColor = glm::vec3(0.6f, 0.3f, 0.1f);
	//glm::vec3 DoorColor1 = glm::vec3(0.61f, 0.31f, 0.11f);

	Cube cube;
	Cube cube2;
	Wall walls;
	NPC npc;
	Trophy trophy;

	float speed = 0.1f;
	float MovementX{0};
	float MovementZ{ 0 };
	vec3 Cameraposition;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.01f, 0.01f, 0.1f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		
		//Cube movement
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //left
		{
			MovementX += speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //right
		{
			MovementX -= speed;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //back
		{
			MovementZ -= speed;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //forward
		{
			MovementZ += speed;
		}

		glm::vec3 doorMove = glm::vec3(0.0f, 0.0f, 0.0f);
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			////doorMove = glm::vec3(-doorWidth, 0.f, 0.01f);
			//glm::vec4 vec(doorPosition, 1.0f);
			//glm::mat4 trans = glm::mat4(1.0f);
			//trans = glm::rotate(trans, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
			//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
			//vec = trans * vec;
			//doorPosition.y = vec.y;
			
		} 

		


		//Cube
		cube.CreateCube(glm::vec3(-0.1f * MovementX, 0, -0.1f * MovementZ), glm::vec3(0.2f,0.2f,0.2f), 0.f);

		cube2.CreateCube(glm::vec3(1, 0, 1), glm::vec3(1, 0.5f, 1),0);
		walls.CreateHouse(glm::vec3(-2,0,-2),glm::vec3(2,1,2));
		npc.CreateNPC(glm::vec3(0, 0, 0), glm::vec3(0.5f, .5f, .5f));
		trophy.CreateTrophy(vec3(1, 0, -2), vec3(0.2f, .2f, .2f));
		//DrawCoordinateSystem(verticesCoordinate);

		//floor
	//	walls.CreateYWall(glm::vec3(-10, 0, -10),glm::vec3( 20,20, 20), glm::vec3(0, 0.8f, 0.2f), glm::vec3(0, 0.2f, 0));

		//Door
		//DrawSquare(XOrientation(doorPosition, doorWidth, doorHeight, DoorColor, DoorColor1));
	//	walls.CreateXWall(glm::vec3(doorPosition.x + doorMove.x, doorPosition.y + doorMove.y, doorPosition.z + doorMove.z),glm::vec3(doorWidth, doorHeight, 1), DoorColor, DoorColor1);

		//House around door
		//walls.CreateXWall(glm::vec3(doorPosition.x + doorWidth, doorPosition.y, doorPosition.z), glm::vec3(houseWidth / 2, houseHeight,0.1f), WallColor, WallColor1);
	//	walls.CreateXWall(glm::vec3(doorPosition.x - (houseWidth / 2) , doorPosition.y, doorPosition.z), glm::vec3(houseWidth / 2, houseHeight, 1), WallColor, WallColor1);

		//walls.CreateZWall(glm::vec3(doorPosition.x - (houseWidth / 2), doorPosition.y, doorPosition.z - houseWidth), glm::vec3(1, houseHeight, houseWidth), WallColor, WallColor1);
		//walls.CreateZWall(glm::vec3(doorPosition.x + (houseWidth / 2) + doorWidth, doorPosition.y, doorPosition.z - houseWidth), glm::vec3(1, houseHeight, houseWidth), WallColor, WallColor);

		//walls.CreateXWall(glm::vec3(doorPosition.x - (houseWidth / 2), doorPosition.y, doorPosition.z - houseWidth), glm::vec3(houseWidth + doorWidth, houseHeight, 1), WallColor, WallColor1);
		//walls.CreateXWall(glm::vec3(doorPosition.x, doorPosition.y + doorHeight, doorPosition.z), glm::vec3(doorWidth, houseHeight - doorHeight, 1), WallColor, WallColor1);

		//Roof
		//walls.CreateYWall(glm::vec3(doorPosition.x - (houseWidth / 2), doorPosition.y + houseHeight, doorPosition.z - houseWidth), glm::vec3(houseWidth + doorWidth, 1,houseWidth), WallColor, WallColor1);

		float Degree;
		if(cube.AABB.TestAABBAABB(cube2.AABB)|| cube.AABB.TestAABBAABB(walls.AABB)||cube.AABB.TestAABBAABB(npc.NPCBox)|| cube.AABB.TestAABBAABB(trophy.AABB))
		{
			walls.WallColor = glm::vec3(0.f, 1.f, 1.f);
			cout << "colliding" << endl;
			//Cameraposition = glm::vec3(-1.5f,1,-2);
			//Degree = 90.f;
			npc.Color = glm::vec3(1, 1, 0);
		}
		else if (!cube.AABB.TestAABBAABB(cube2.AABB) || !cube.AABB.TestAABBAABB(walls.AABB))
		{
			walls.WallColor = glm::vec3(1.f, 0, 1.f);
			cout << "not colliding" << endl;
			//Cameraposition = glm::vec3(glm::vec3((-0.1f * MovementX), 1.f, (-0.1f * MovementZ) + 5));
			//Degree = 45.f;
			npc.Color = glm::vec3(1, 0, 1);
		}
		//Camera
		Cameraposition = glm::vec3(glm::vec3((-0.1f * MovementX), 1.f, (-0.1f * MovementZ) + 5));
		Degree = 45.f;
		Camera camera(width, height, Cameraposition);
		camera.Inputs(window);
		camera.Matrix(Degree, .1f, 100.0f, shaderProgram, "camMatrix");
		
		//Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;

}
