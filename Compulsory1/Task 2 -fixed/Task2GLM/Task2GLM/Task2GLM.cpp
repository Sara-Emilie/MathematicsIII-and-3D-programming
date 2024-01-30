// Task2GLM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <iomanip>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
"uniform mat4 model; // model matrix\n"
"out vec3 fragColor;\n"
"void main()\n"
"{\n"
"   gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   // Change color based on x, y, and z positions\n"
"   float colorValueX = (aPos.x + 1.0) / 2.0; // Map x to [0, 1]\n"
"   float colorValueY = (aPos.y + 1.0) / 2.0; // Map y to [0, 1]\n"
"   float colorValueZ = (aPos.z + 1.0) / 2.0; // Map z to [0, 1]\n"
"   fragColor = vec3(colorValueX, colorValueY, colorValueZ); // RGB based on x, y, z\n"
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



struct Vertex
{
    GLfloat x, y, z, r, g, b; // not using u and v for now
};


void writeSpiralDataToFile(const char* fileName, int numPoints) {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    const double pi = 3.14159265358979323846;
    const double pointsPerTurn = 100.0;
    const double initialRadius = 0.1;
    const double pitch = 0.06;

    for (int i = 0; i < numPoints; ++i) {
        double radius = initialRadius + 0.0005 * i;
        double theta = 2.0 * pi * i / pointsPerTurn;
        double x = radius * cos(theta);
        double y = radius * sin(theta);
        double z = pitch * i / pointsPerTurn;


        // Use your color logic here
        GLfloat r = 1.0f;
        GLfloat g = 0.0f;
        GLfloat b = 0.0f;

        outputFile << std::fixed << std::setprecision(3);
        outputFile << x << ", " << y << ", " << z << ", " << r << ", " << g << ", " << b << std::endl;
    }

    outputFile.close();
}


void drawSpiral(const char* fileName) {
    vector<Vertex> vertices;

    // Read the data from the file //
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Unable to open file: " << fileName << endl;
        return;
    }

    char comma;

    Vertex vertex;
    while (inputFile >> vertex.x >> comma >> vertex.y >> comma >> vertex.z >> comma >> vertex.r >> comma >> vertex.g >> comma >> vertex.b) {
        vertices.push_back(vertex);
    }

    inputFile.close();

    ///////////////////////////////////////////////////////////////////////


    // glfw: initialize
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // set version and core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Spiral", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create the GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }



    /////////////////////////////////////////////////////////////////////////

    // Build and compile our shader program //

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ///////////////////////////////////////////////////////////////////////////


    // Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // Set vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
        // render loop
        while (!glfwWindowShouldClose(window)) {

            // input
            processInput(window);

            // clear the color buffer
            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // use shader programs
            glUseProgram(shaderProgram);

            // bind VAO
            glBindVertexArray(VAO);

            // apply rotation around the z-axis
            float angle = glfwGetTime(); // time-based rotation
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.5f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(rotation));

            glLineWidth(3.0f);

            // draw the spiral
            glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

            // unbind VAO
            glBindVertexArray(0);

            // swap buffers and poll IO events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    // clean up resources after the rendering loop
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

