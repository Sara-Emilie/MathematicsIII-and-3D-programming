// Newtons Metode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;

//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec2 aPos;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\0";
//


double f(double x) //f(x) = x^2 - 2
{
	return pow(x,2)-2;
}

double df(double x) //f'(x) = 2x
{
	return 2*x;
}

pair<double, int> newton(double x0)
{
	int iter{ 0 };
	auto fx = f(x0);
	double x = x0;
	while (abs(fx) > 0.01)
	{
		x = x - fx / df(x);
		fx = f(x);
		iter++;

        cout << fx << ", Iterations: " << iter << endl;
	}
	return pair<double, int>(x, iter);
}

void writeToFile(const char* fileName, double x, double y) {
    ofstream outputFile(fileName, ios::app);  // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile << std::fixed << std::setprecision(3);
        outputFile << x << " " << y;


    }
    else {
        cerr << "Unable to open the output file for writing." << endl;
    }
    if (y > 0) {
        outputFile << " green";  // Use green for positive y
    }
    else if (y < 0) {
        outputFile << " red";    // Use red for negative y
    }
    else {
        outputFile << " black";  // Use black for y = 0
    }
    outputFile << endl;
    outputFile.close();

int main()
{
	/*auto par = newton(1);
	cout << "Root: " << par.first << ", Iterations: " << par.second << endl;*/

    //const char* outputFileName = "outputfile.txt";

      //def mengde
    double lower_bound = -100.0;
    double upper_bound = 100.0;
    const char* outputFileName = "output.txt";

    // Open the file for writing


    ofstream clearFile(outputFileName);
    clearFile.close();

    auto par = newton(5, lower_bound, upper_bound, outputFileName);

    if (par.first >= lower_bound && par.first <= upper_bound) {
        std::cout << "Root: " << par.first << " Iterations: " << par.second << std::endl;
    }
    else {
        std::cout << "No root found within the specified interval." << std::endl;
    }
    ofstream updateFile(outputFileName, ios::in | ios::out);
    if (updateFile.is_open()) {
        updateFile.seekp(0);
        updateFile << "Number of Points: " << par.second << endl;
        updateFile.close();
    }
    else {
        cerr << "Error unable to update file" << endl;
    }
    return 0;

    //if (!glfwInit())
    //    return -1;
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Graph window", NULL, NULL);
    //if (window == NULL)
    //{
    //    std::cout << "Failed to create the GLFW window" << std::endl;
    //    glfwTerminate();
    //    return -1;
    //}

    //glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    std::cout << "Failed to initialize GLAD" << std::endl;
    //    return -1;
    //}

    //unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexShader);

    //int success;
    //char infoLog[512];
    //glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    //}

    //unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //glCompileShader(fragmentShader);

    //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    //}

    //unsigned int shaderProgram = glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);

    //glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //if (!success) {
    //    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    //}
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);

    //// Set up vertex data (and buffer(s)) and configure vertex attributes
    //float vertices[SCR_WIDTH * 2]; // Assuming one point for each pixel in the width
    //for (int i = 0; i < SCR_WIDTH; ++i)
    //{
    //    float x = (static_cast<float>(i) / SCR_WIDTH) * 2.0f - 1.0f; // Map i to the range [-1, 1]
    //    float y = x * x - 2.0f; // Calculate y based on the function x^2 - 2
    //    vertices[i * 2] = x;
    //    vertices[i * 2 + 1] = y;
    //}

    //unsigned int VBO, VAO;
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);

    //glBindVertexArray(VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    //while (!glfwWindowShouldClose(window))
    //{
    //    processInput(window);

    //    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    glUseProgram(shaderProgram);
    //    glBindVertexArray(VAO);

    //    glDrawArrays(GL_LINE_STRIP, 0, SCR_WIDTH);

    //    // Set a thicker line width
    //    glLineWidth(10.0f); // Adjust the thickness as needed

    //    glfwSwapBuffers(window);
    //    glfwPollEvents();
    //}

    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);

    //glfwTerminate();

}

//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//    std::cout << "Window resized with width " << width << " and height " << height << std::endl;
//}
