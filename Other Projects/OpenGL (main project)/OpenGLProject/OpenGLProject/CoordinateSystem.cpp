#include "CoordinateSystem.h"


CoordinateSystem::CoordinateSystem()
{

};
void CoordinateSystem::CreateCoordinateSystem(std::vector<CoordinateSystemVertex>& vertices, float start, float iterations) {

	// X-axis
	for (float i = start; i < iterations; ++i) {
		float n = 0.05f;
		float x = i * n;
		float y = 0.0;
		float z = 0.0f;
		CoordinateSystemVertex vertex;
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
		CoordinateSystemVertex vertex;
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
		CoordinateSystemVertex vertex;
		vertex.x = x;
		vertex.y = y;
		vertex.z = z;
		vertex.r = 0.0f;
		vertex.g = 0.0f;
		vertex.b = 1.0f;  // Adjust for coloring effect
		vertices.push_back(vertex);
	}
};

void CoordinateSystem::DrawCoordinateSystem(std::vector<CoordinateSystemVertex> vertices)
{
	// Draw coordinate system
	VAO coordinateVAO;
	coordinateVAO.Bind();

	// Create VBO object and initialize it with vertex data
	VBO coordinateVBO(reinterpret_cast<GLfloat*>(vertices.data()), static_cast<GLsizeiptr>(vertices.size() * sizeof(CoordinateSystemVertex)));
	coordinateVBO.Bind();

	// Specify vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CoordinateSystemVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CoordinateSystemVertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind VBO and VAO
	coordinateVBO.Unbind();
	coordinateVAO.Unbind();

	// Draw coordinate system
	coordinateVAO.Bind();
	//glDrawArrays(GL_LINES, 0, vertices.size());
	glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(vertices.size()));
	coordinateVAO.Unbind();

	coordinateVBO.Delete();
	coordinateVAO.Delete();
};

