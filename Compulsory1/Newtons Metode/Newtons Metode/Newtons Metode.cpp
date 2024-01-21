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

// Task 1.1, 1.2 and 1.3
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
    while (abs(fx) > 0.01 && x >= lower_bound && x <= upper_bound)
    {
        x = x - fx / df(x);
        fx = f(x);
        iter++;

        cout << fx << ", Iterations: " << iter << endl << endl;
    }
    return pair<double, int>(x, iter);
}

//Task 1.4 and 1.5

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



struct vertex
{
    float x, y, z, r, g, b, u, v; //I'm only using x,y and r,g 
};

void writeToFile(const char* fileName, /*double x, double y, float r, float g*/ const vector<vertex>& vertices)
{
   
    std::ofstream outputFile(fileName);  // Open the file (overwrite existing content)
    if (outputFile.is_open()) {
        outputFile << "Number of points: " << vertices.size() << std::endl;  // Write the total number of points

        for (const auto& vertex : vertices) {
            outputFile << std::fixed << std::setprecision(3);
            outputFile << "X: " << vertex.x << " Y: " << vertex.y;

            if (vertex.y > 0) {
                outputFile << " Over 0";  // positive y
            }
            else if (vertex.y < 0) {
                outputFile << " Under 0";  // negative y
            }
            else {
                outputFile << " Y = 0 ";  // y = 0
            }

            outputFile << " R: " << vertex.r << " G: " << vertex.g << std::endl;
        }

        outputFile.close();
    }
    else {
        std::cerr << "Unable to open the output file for writing." << std::endl;
    }
  
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

  
 vector<vertex> createFunction(int iterations, int start, const char* filename)
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
            }
            else {
                //decreasing
                Vertex.r = 1.0f;
                Vertex.g = 0.0;
            }
            mVertices.push_back(Vertex);
            //writeToFile(filename, Vertex.x, Vertex.y, Vertex.r, Vertex.g);
            writeToFile(filename, mVertices);
            cout << "X = " << Vertex.x << " " << "Y = " << Vertex.y << "The derivate: " << y2 << endl;

        }
        return mVertices;
    };

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        cout << "Window resized with width " << width << " and height " << height << endl;
    }

    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void drawFunction(const vector<vertex>& vertices)
    {
        //Initialize GLFW
        if (!glfwInit())
        {
           cerr << "Failed to initialize GLFW" << endl;
           return;
        }

        //Set version of glfw to 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Set profile to core

        //Create the GLFW window aswell as it's OpenGL context
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Graph window", NULL, NULL);
        if (window == NULL)
        {
            cout << "Failed to create the GLFW window" << endl;
            glfwTerminate();
            return;
        }

        //Make the window the current context
        glfwMakeContextCurrent(window);


        //Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cout << "Failed to initialize GLAD" << endl;
            return;
        }

        //Set the viewport
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        //Set the callback function for when the window is resized
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Set the callback function for window resize
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Set up OpenGL rendering state
        glEnable(GL_PROGRAM_POINT_SIZE);
        glPointSize(5.0f);

        // Vertex Buffer Object (VBO) and Vertex Array Object (VAO) setup
        GLuint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Unbind VAO
        glBindVertexArray(0);

        // Shader setup (vertex and fragment shaders)
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aColor;\n"
            "out vec3 ourColor;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos, 1.0);\n"
            "   ourColor = aColor;\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec3 ourColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(ourColor, 1.0f);\n"
            "}\n\0";

        // Compile shaders
        GLuint vertexShader, fragmentShader, shaderProgram;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        // Check for vertex shader compilation errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Fragment shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        // Check for fragment shader compilation errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check for shader linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Delete shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Render loop
        while (!glfwWindowShouldClose(window))
        {
            // Process user input
            processInput(window);

            // Clear the screen
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Use our shader program
            glUseProgram(shaderProgram);

            // Draw the function using the VAO
            glBindVertexArray(VAO);
            glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

            // Swap the front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }

        // Clean up
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        glfwTerminate();
    
	}

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

    auto vertices = createFunction(5, -2, outputFileName);

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


    drawFunction(vertices);

    return 0;

    
   
    //glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


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


