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

#include <Eigen/Dense>

#include "Shaders/ShaderClass.h"
#include "Shaders/VAO.h"
#include "Shaders/VBO.h"
#include "Shaders/EBO.h"
#include "Camera.h"
using namespace std;
using namespace Eigen;


// Window dimensions
const unsigned int width = 800;
const unsigned int height = 800;

struct Vertex 
{
	float x, y, z;
	float r, g, b;
	//float pr, pg, pb;
};

unsigned int Indices[] = 
{

	0,1,2,  // Front face
	3,1,2,

	7,5,4,  // Back face
	6,4,5,

	4,2,6,  // Top face
	3,6,2,

	7,0,5, // Bottom face
	1,5,0,

	//7,2,0,  // Left face
	//7,2,4,

	2,7,0
	,2,4,7,

	5,3,1,  // Right face
	5,3,6

	

};




void CreateCoordinateSystem(std::vector<Vertex>& vertices, float start, float iterations) {
	
	// X-axis
	for (float i = start; i < iterations; ++i) {
		float n = 0.05f;
		float x = i * n;
		float y = 0.0;
		float z = 0.0f;
		Vertex vertex;
		vertex.x = x;
		vertex.y = y;
		vertex.z = z;
		vertex.r = 1.0f;
		vertex.g = 0.0f;
		vertex.b = 0.0f;  // Adjust for coloring effect
		vertices.push_back(vertex);
	}

	// Y-axis
	for (float i = start; i < iterations; ++i) {
		float n = 0.05f;
		float x = 0.0;
		float y = i * n;
		float z = 0.0f;
		Vertex vertex;
		vertex.x = x;
		vertex.y = y;
		vertex.z = z;
		vertex.r = 0.0f;
		vertex.g = 1.0f;
		vertex.b = 0.0f;  // Adjust for coloring effect
		vertices.push_back(vertex);
	}
	// Z - Axis
	for (float i = start; i < iterations; ++i) {
		float n = 0.05f;
		float x = 0.0;
		float y = 0.0f;
		float z = i * n;
		Vertex vertex;
		vertex.x = x;
		vertex.y = y;
		vertex.z = z;
		vertex.r = 0.0f;
		vertex.g = 0.0f;
		vertex.b = 1.0f;  // Adjust for coloring effect
		vertices.push_back(vertex);
	}
}



void writeToFile(const char* fileName, double x, double y, double z, double r, double g, double b) {
	std::ofstream outputFile(fileName, std::ios::app);  // Open the file in append mode
	if (outputFile.is_open()) {
		outputFile << std::fixed << std::setprecision(3);
		outputFile << x << " , " << y << " , " << z << " , " << r << " , " << g << " , " << b;


	}
	else {
		std::cerr << "Unable to open the output file for writing." << std::endl;
	}
	outputFile << std::endl;
	outputFile.close();
}

void Readfile(const char* fileName, std::vector<Vertex>& verticesSpiral) {
	std::ifstream inputFile(fileName);
	if (inputFile.is_open()) {


		std::string line;
		std::getline(inputFile, line);
		Vertex vertex;
		char comma; // to capture the commas in the file

		while (inputFile >> vertex.x >> comma >> vertex.y >> comma >> vertex.z >> comma
			>> vertex.r >> comma >> vertex.g >> comma >> vertex.b) {
			verticesSpiral.push_back(vertex);
		}

		inputFile.close();
	}
	else {
		std::cerr << "Unable to open the input file for reading." << std::endl;
	}
}

void DrawCoordinateSystem(std::vector<Vertex> vertices)
{
	// Draw coordinate system
	VAO coordinateVAO;
	coordinateVAO.Bind();

	// Create VBO object and initialize it with vertex data
	VBO coordinateVBO(reinterpret_cast<GLfloat*>(vertices.data()), static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)));
	coordinateVBO.Bind();

	// Specify vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind VBO and VAO
	coordinateVBO.Unbind();
	coordinateVAO.Unbind();

	// Draw coordinate system
	coordinateVAO.Bind();
	glDrawArrays(GL_LINES, 0, vertices.size());
	coordinateVAO.Unbind();
}

void DrawSquare(vector<Vertex> points )
{
	//Draw Square
	VAO SquareVAO;
	SquareVAO.Bind();

	VBO SquareVBO(reinterpret_cast<GLfloat*>(points.data()), static_cast<GLsizeiptr>(points.size() * sizeof(Vertex)));
	SquareVBO.Bind();



	//Specify vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	EBO SquareEBO(Indices, sizeof(Indices));
	/*glGenBuffers(1, &EBO);*/
	/*glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	SquareEBO.Bind();

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	SquareVAO.Unbind();
	SquareVBO.Unbind();
	SquareEBO.Unbind();

}
void BoxDraw(glm::vec3 position, float scale, float rotation)
{
	vector<Vertex> Squarepoints;
	Squarepoints.push_back(Vertex{ position.x,position.y,position.z,1,1,0 });
	Squarepoints.push_back(Vertex{ position.x+scale,position.y,position.z,1,0,1 });
	Squarepoints.push_back(Vertex{ position.x,position.y+scale,position.z,1,0,0 });
	Squarepoints.push_back(Vertex{ position.x+scale,position.y+scale,position.z,0,0,0 });

	Squarepoints.push_back(Vertex{ position.x,position.y + scale,position.z+scale,1,0,0.5f });
	Squarepoints.push_back(Vertex{ position.x + scale,position.y,position.z+scale,0.5f,0.2f,0 });
	Squarepoints.push_back(Vertex{ position.x + scale,position.y + scale,position.z+scale,1,1,1 });
	Squarepoints.push_back(Vertex{ position.x,position.y,position.z+ scale,1,0.3f,0.4f });


	DrawSquare(Squarepoints);

}
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




	// Create vector to store vertices & Generate coordinate system
	std::vector<Vertex> verticesCoordinate;
	CreateCoordinateSystem(verticesCoordinate, -10, 10); // Ranges from -10 to 10

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	//Camera 
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 500.0f, shaderProgram, "camMatrix");


		

		BoxDraw(glm::vec3(-0.1f,-0.1f,-0.1f),0.2f,0.f);

		DrawCoordinateSystem(verticesCoordinate);

		// Swap the back buffer with the front buffer
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

