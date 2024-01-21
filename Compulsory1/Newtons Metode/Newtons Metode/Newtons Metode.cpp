// Newtons Metode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
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

void writeToFile(const char* fileName, double x, double y, float r, float g)
{
    ofstream outputFile(fileName, ios::app);  // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile << std::fixed << std::setprecision(3);
        outputFile << x << " " << y;


    }
    else {
        cerr << "Unable to open the output file for writing." << endl;
    }
    if (y > 0) {
        outputFile << " Over 0";  // positive y
    }
    else if (y < 0) {
        outputFile << " Under 0";    // negative y
    }
    else {
        outputFile << " y = 0 ";  //  y = 0
    }
    outputFile << endl;
    outputFile.close();
}


double f(double x) //f(x) = x^2 - 2
{
    return pow(x, 2) - 2;
}

double df(double x) //f'(x) = 2x
{
    return 2 * x;
}

pair<double, int> newton(double x0, double lower_bound, double upper_bound, const char* file)
{
    int iter{ 0 };
    auto fx = f(x0);
    double x = x0;
    writeToFile(file, x, fx, 0, 0);
    while (abs(fx) > 0.01 && x >= lower_bound && x <= upper_bound)
    {
        x = x - fx / df(x);
        fx = f(x);
        iter++;

        cout << fx << ", Iterations: " << iter << endl;
    }
    return pair<double, int>(x, iter);
}

void printNewton(pair<double, int> par, double lower_bound, double upper_bound)
{
    //print out the root and iterations
    if (par.first >= lower_bound && par.first <= upper_bound)
    {
        cout << "Root: " << par.first << " Iterations: " << par.second << std::endl;
    }
    else
    {
        std::cout << "No root found within the specified interval." << std::endl;
    }

}

    struct vertex
    {
        float x, y, z, r, g, b, u, v;
    };

    void createFunction(int iterations, int start, const char* filename)
    {
        float n = 0.05f;
        float x0, x1, y0, y1, y2;

        x0 = 0.00f, y0 = 0.0f;


        vertex Vertex; // x ,y , z, r, g, b, u, v
        vector<vertex> mVertices;

        
        for (int i = start; i < iterations; i++) {
            //float x = i * n;

            //float y = x * x;

            x1 = i * n;
            y1 = x1 * x1 - 2;
            y2 = 2 * x1;

            x0 = x1;
            y0 = x1;

            Vertex.x = x1;
            Vertex.y = y1;

            if (y1 > y0) {
                //rising
                Vertex.r = 0.0f;
                Vertex.g = 1.0f;
                Vertex.b = 0.0f;
            }
            else {
                //decreasing
                Vertex.r = 1.0f;
                Vertex.g = 0.0;
                Vertex.b = 0.0f;
            }
            mVertices.push_back(Vertex);
            writeToFile(filename, Vertex.x, Vertex.y, Vertex.r, Vertex.g);
            cout << "X = " << Vertex.x << " " << "Y = " << Vertex.y << "The derivate: " << y2 << endl;

        }
    };

int main()
{
	/*auto par = newton(1);
	cout << "Root: " << par.first << ", Iterations: " << par.second << endl;*/

    //const char* outputFileName = "outputfile.txt";

    //define upper and lower bound
    double lower_bound = -100.0;
    double upper_bound = 100.0;


    const char* outputFileName = "output.txt";

   
    ofstream clearFile(outputFileName); // Open the file in append mode
    clearFile.close(); // Clear the file contents
   

    auto par = newton(5, lower_bound, upper_bound, outputFileName); //do newton method with 5 iterations

    printNewton(par, lower_bound, upper_bound); //print out the root and iterations

    /*ofstream updateFile(outputFileName, ios::in | ios::out);
    if (updateFile.is_open())
    {
        updateFile.seekp(0);
        updateFile << "Number of Points: " << par.second << endl;
        updateFile.close();
    }
    else
    {
        cerr << "Error unable to update file" << endl;
    }*/

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
