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
double f(double x) //f(x) = x^2 - 2
{
    return pow(x, 2) - 2;
}


// Calculate the derivative of a function at a point
double calculateDerivative(double (*function)(double), double x, double h = 1e-8) 
{
    return (function(x + h) - function(x)) / h;
}

//Vertex struct
struct vertex
{
    float x, y, z, r, g, b, u, v; //I'm only using x,y and r,g 
};


//main function
void dataPoints(double x0, double lower_bound, double upper_bound, int iter) 
{
    double h = (upper_bound - lower_bound) / iter; // Calculate the step size
	double x = x0;
	double y = f(x);
    double x_next = x + h;
	double y_next = f(x + h);

    vertex Vertex;
    vector<vertex> vertices;
    vector<vertex> openGLvertices; //all points are divided by 10 to fit in the screen

    for (int i = 0; i < iter; i++)
    {
        double derivative = calculateDerivative(f, x);

        if (y_next > y)
        {
			outputFile(x, y, derivative, "Green");

            Vertex.r = 0.0f;
            Vertex.g = 1.0f;
            Vertex.b = 0.0f;

            Vertex.x = x;
            Vertex.y = y;
            
            vertices.push_back(Vertex);

            Vertex.x = x /10;
            Vertex.y = y /10;
            openGLvertices.push_back(Vertex);


		}
        else if (y_next == y)
        {
            outputFile(x, y, derivative, "White");

            Vertex.r = 1.0f;
            Vertex.g = 1.0f;
            Vertex.b = 1.0f;

            Vertex.x = x;
            Vertex.y = y;
            vertices.push_back(Vertex);

            Vertex.x = x / 10;
            Vertex.y = y / 10;
            openGLvertices.push_back(Vertex);


        }
        else
        {
			outputFile(x, y, derivative, "Red");

            Vertex.r = 1.0f;
			Vertex.g = 0.0f;
			Vertex.b = 0.0f;

			Vertex.x = x;
			Vertex.y = y;
			vertices.push_back(Vertex);

			Vertex.x = x / 10;
			Vertex.y = y / 10;
			openGLvertices.push_back(Vertex);
		}

		x = x_next;
		y = y_next;
		x_next = x + h;
		y_next = f(x + h);
	}

}


int main()
{

   double lower_bound = -2;
   double upper_bound = 2;
   int iter = 100;

   double x0 = lower_bound;

   numberOfoints(iter);
   dataPoints(x0, lower_bound, upper_bound, iter);

}


//known bug: the output file will be written twice if the program is run twice...