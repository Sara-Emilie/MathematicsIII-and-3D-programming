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



// Window dimensions
const unsigned int width = 800;
const unsigned int height = 800;

struct Vertex 
{
	float x, y, z;
	float r, g, b;
	//float pr, pg, pb;
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


Eigen::MatrixXd X_Matrix(8, 3);
Eigen::MatrixXd Y_Matrix(8, 1);

void CalculateParabola(std::vector<Vertex>& verticesParabola)
{
	X_Matrix << 1, 1, 1,
		4, 2, 1,
		9, 3, 1,
		16, 4, 1,
		25, 5, 1,
		36, 6, 1,
		49, 7, 1,
		64, 8, 1;

	Y_Matrix << 2,
		3,
		5,
		6,
		5,
		4,
		3,
		2;

	Eigen::MatrixXd A_Transpose = X_Matrix.transpose();

	Eigen::MatrixXd B_Matrix = A_Transpose * X_Matrix;
	Eigen::MatrixXd B_Inverse = B_Matrix.inverse();
	Eigen::MatrixXd C_Matrix = A_Transpose * Y_Matrix;
	Eigen::MatrixXd A_Matrix = B_Inverse * C_Matrix;

	cout << "A_Matrix: " << A_Matrix << endl;

	for (int i = 0; i < 8; i++)
	{
		float x = static_cast<float>(i);
		float y = A_Matrix(0, 0) * x * x + A_Matrix(1, 0) * x + A_Matrix(2, 0);

		cout << "x: " << x << " y: " << y << endl;
		verticesParabola.push_back(Vertex{ x / 10, y / 10, 0.0f, 1.0f, 1.0f, 0.0f });
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




	// Create vector to store vertices
	std::vector<Vertex> verticesCoordinate;
	// Generate coordinate system
	CreateCoordinateSystem(verticesCoordinate, -10, 10); // Ranges from -10 to 10

	// Create vector to store vertices for the parabola
	std::vector<Vertex> verticesParabola;
	// Calculate parabola
	CalculateParabola(verticesParabola);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");


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


		// Draw coordinate system
		VAO coordinateVAO;
		coordinateVAO.Bind();

		// Create VBO object and initialize it with vertex data
		VBO coordinateVBO(reinterpret_cast<GLfloat*>(verticesCoordinate.data()), static_cast<GLsizeiptr>(verticesCoordinate.size() * sizeof(Vertex)));

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
		glDrawArrays(GL_LINES, 0, verticesCoordinate.size());
		coordinateVAO.Unbind();


		// Draw parabola
		VAO parabolaVAO;
		parabolaVAO.Bind();

		// Create VBO object and initialize it with vertex data
		VBO parabolaVBO(reinterpret_cast<GLfloat*>(verticesParabola.data()), static_cast<GLsizeiptr>(verticesParabola.size() * sizeof(Vertex)));

		// Specify vertex attribute pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Unbind VBO and VAO
		parabolaVBO.Unbind();
		parabolaVAO.Unbind();

		// Draw parabola
		parabolaVAO.Bind();
		glDrawArrays(GL_LINE_STRIP, 0, verticesParabola.size());
		parabolaVAO.Unbind();

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

