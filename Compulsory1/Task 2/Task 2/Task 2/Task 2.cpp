// Task 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <cstddef>

using namespace std;

//Create a file with data points for a three - dimensional spiral, as explained in ? ? .
//Choose a step length for the parameter t and 
//vertex colors at your discretion.Use the same file format as in the previous task.


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 fragColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   fragColor = color;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 fragColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(fragColor, 1.0);\n"
"}\n\0";


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        std::cout << "A key pressed ..." << std::endl;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    std::cout << " windows resized with " << width << " Height " << height << std::endl;
}


void writeSpiralDataToFile(const char* fileName, int numPoints) {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    const double pi = 3.14159265358979323846;
    const double step = 0.1; // Adjust the step length as needed
    const double heightScale = 0.1; // Adjust the height scale as needed

    for (int i = 0; i < numPoints; ++i) {
        double t = step * i;
        double x = cos(t);
        double y = sin(t);
        double z = heightScale * t;

        // Use your color logic here
        GLfloat r = static_cast<GLfloat>(std::sin(t));
        GLfloat g = static_cast<GLfloat>(std::cos(t));
        GLfloat b = static_cast<GLfloat>(std::abs(std::sin(t * 2.0)));

        outputFile << std::fixed << std::setprecision(3);
        outputFile << x << ", " << y << ", " << z << ", " << r << ", " << g << ", " << b << std::endl;
    }

    outputFile.close();
}

struct Vertex
{
    GLfloat x, y, z, r, g, b, u, v; //I'm only using x,y,z and r,g,b
};


void drawSpiral(const char* fileName) {
    vector<Vertex> vertices;

    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Unable to open file: " << fileName << endl;
        return;
    }

    char comma;

    Vertex vertex;
    while (inputFile >> vertex.x >> comma >> vertex.y >> comma >> vertex.z >> comma >> vertex.r >> comma >> vertex.g >> comma >> vertex.b >> comma >> vertex.u >> comma>> vertex.v) {
        vertices.push_back(vertex);
    }

    inputFile.close();

    // glfw: initialize
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Spiral", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create the GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(reinterpret_cast<size_t>(&reinterpret_cast<Vertex*>(0)->r)));

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
}


int main()
{
    const char* fileName = "spiral_data.txt";
    int numPoints = 1000; // Adjust the number of points as needed

    writeSpiralDataToFile(fileName, numPoints);

    drawSpiral(fileName);

    std::cout << "Spiral data written to " << fileName << std::endl;

}

