// Task 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


// screen settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Vertex shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n" // x, y
"layout (location = 1) in vec3 color;\n" // r, g, b
"out vec3 fragColor;\n" // Pass color directly to the fragment shader
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"   fragColor = color;\n" // Use the color directly from the input attribute
"}\0";

//Fragment shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 fragColor;\n" // Interpolated color from vertex shader
"out vec4 finalColor;\n"
"void main()\n"
"{\n"
"   finalColor = vec4(fragColor, 1.0);\n"
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

// WRITE TO FILE
void outputFile(double x, double y, double derivative, string n)
{
    const char* fileName = "outputfile.txt";
    ofstream outputFile(fileName, ios::app);
    if (outputFile.is_open())
    {
        outputFile << fixed << setprecision(3);
        outputFile << x << ", " << y << ", 0.0, " << " Derivative is: " << derivative <<" color -->" << n << endl;
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
    outputFile.close();
}

void numberOfoints(int iter)
{
	const char* fileName = "outputfile.txt";
	ofstream outputFile(fileName, ios::app);
    if (outputFile.is_open())
    {
		outputFile << fixed << setprecision(3);
		outputFile << "Number of points: " << iter << endl;
	}
    else
    {
		std::cout << "Unable to open file" << std::endl;
	}
	outputFile.close();
}

//Function
double f(double x) //f(x)=sin(2*sin(2*sin(2*sin(x))))
{
    return  std::sin(2 * std::sin(2 * std::sin(2 * std::sin(x))));
}


// Calculate the derivative of a function at a point
double calculateDerivative(double (*function)(double), double x, double h = 1e-8) 
{
    return (function(x + h) - function(x)) / h;
}

//Vertex struct
struct vertex
{
    GLfloat x, y, z, r, g, b, u, v; //I'm only using x,y and r,g 

   
};


// function to make datapoints
vector<vertex> dataPoints(double x0, double lower_bound, double upper_bound, int iter)
{
    double h = (upper_bound - lower_bound) / iter; // Calculate the step size
	double x = x0;
	double y = f(x);
    double x_next = x + h;
	double y_next = f(x + h);

    vertex Vertex;
    vector<vertex> openGLvertices; //all points are divided by 5 to fit in the screen

    for (int i = 0; i < iter; i++)
    {
        double derivative = calculateDerivative(f, x);

        if (y_next > y)
        {
			outputFile(x, y, derivative, "Green");

            Vertex.r = 0.0f;
            Vertex.g = 1.0f;
            Vertex.b = 0.0f;


            Vertex.x = x /5;
            Vertex.y = y /5;
            openGLvertices.push_back(Vertex);


		}
        else if (y_next == y)
        {
            outputFile(x, y, derivative, "White");

            Vertex.r = 1.0f;
            Vertex.g = 1.0f;
            Vertex.b = 1.0f;

            Vertex.x = x / 5;
            Vertex.y = y / 5;
            openGLvertices.push_back(Vertex);


        }
        else
        {
			outputFile(x, y, derivative, "Red");

            Vertex.r = 1.0f;
			Vertex.g = 0.0f;
			Vertex.b = 0.0f;

			Vertex.x = x / 5;
			Vertex.y = y / 5;
			openGLvertices.push_back(Vertex);
		}

		x = x_next;
		y = y_next;
		x_next = x + h;
		y_next = f(x + h);
	}


   
    return openGLvertices; //, vertices ;
}

void drawFunction(vector<vertex> vertices)
{
    // glfw: initialize  ---------------------------------------------------------------------
    glfwInit();

    //Tell GLFW what version of OpenGL we are using (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Tell GLFW we are using the CORE profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Graph window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create the GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //Make the window the current context
    glfwMakeContextCurrent(window);

   

    //Set the viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // build and compile our shader program //------------------------------------------
   
   // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
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

    //--------------------------------------------------------------------------
   

    // Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and fill VBO with vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);  // x, y
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(3 * sizeof(GLfloat)));  // r, g, b
    glEnableVertexAttribArray(1);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Process input
        processInput(window);

        // Clear the color buffer
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Bind the VAO
        glBindVertexArray(VAO);

        // Draw a line strip connecting the points
        glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

        // Unbind the VAO
        glBindVertexArray(0);
        // Swap the front and back buffers

        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

    
    }

    // clean up resources after the rendering loop
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

}

int main()
{

   double lower_bound = -10;
   double upper_bound = 10;
   int iter = 100;

   double x0 = lower_bound;

   numberOfoints(iter);
   vector<vertex>openGLvertex = dataPoints(x0, lower_bound, upper_bound, iter);
   drawFunction(openGLvertex);
}



//known bug: the output file will be written twice if the program is run twice...