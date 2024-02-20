// ContinueTrying.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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


// flyttet fra main og til egen headerfil (kan bruke flere *.h hvis dere vil)
struct Vertex {
    float x, y, z, r, g, b, u, v;
};

struct Line
{
    std::vector<Vertex> mVertices;
    glm::mat4 matrix;

    Line() : matrix(1.0f) {}
};

struct TriangleSurface
{
    std::vector<Vertex> mVertices;
    glm::mat4 matrix;

    TriangleSurface() : matrix(glm::mat4(1.0f)) {}
};

struct MyIO
{
    static std::string readShader(const char* sourceFile);
};

// returnerer en string, det kan hende vi må bruke
// konvertering med c_str() etterpå
// Nå statisk i egen klasse
std::string MyIO::readShader(const char* sourceFile)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    std::stringstream shaderStream;
    shaderFile.open(sourceFile);

    if (!shaderFile);// Feilmelding
        // Read file's buffer contents into streams
    shaderStream << shaderFile.rdbuf();

    // close file handler
    shaderFile.close();

    // Convert stream into string
    shaderCode = shaderStream.str();
    return shaderCode;
}
// Lager en enkelt trekant i standardkonstruktøren
TriangleSurface::TriangleSurface()
{
    Vertex v0{ 0,0,0,1,0,0,0,0 };
    Vertex v1{ 1,0,0,0,1,0,0,0 };
    Vertex v2{ 0,1,0,0,0,1,0,0 };
    mVertices.push_back(v0);
    mVertices.push_back(v1);
    mVertices.push_back(v2);
}

int main()
{
    int main()
    {
        std::vector<TriangleSurface> surfaces; // tillegg 290124
        std::vector<Line> lines; // tillegg 290124
        int mMatrixUniform; // added 050224
        Camera camera; // added 050224
        // Legg inn objekter som skal rendres med push_back
        TriangleSurface triangle;
        surfaces.push_back(triangle);
        Innlesing av verteks - og fragmentshader i main :
        std::string vs = MyIO::readShader("c:/data/vertexshader.vert");
        vertexShaderSource = vs.c_str();
        3d - programmering week 6 – 5 / 2 / 24
            std::string fs = MyIO::readShader("c:/data/fragmentshader.frag");
        fragmentShaderSource = fs.c_str();

        // build and compile our shader program
        // ------------------------------------
       /* Vi har brukt de samme variabelnavnene som tidligere, så resten av koden i denne bolken
            kan gjenbrukes.
            Neste endring / tillegg følger her :*/


        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        unsigned int VBO, VAO;
        // Tillegg 290124: En løkke for linjeobjekter
        /////////////////////////////////////////////////////////
        for (auto it = lines.begin(); it != lines.end(); it++)
        {
            //Vertex Array Object - VAO
            glGenVertexArrays(1, &mVAO);
            glBindVertexArray(mVAO);
            //Vertex Buffer Object to hold vertices - VBO
            glGenBuffers(1, &mVBO);
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            glBufferData(GL_ARRAY_BUFFER, it->mVertices.size() * sizeof(Vertex),
                it->mVertices.data(), GL_STATIC_DRAW);
            // 1rst attribute buffer : vertices
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                (GLvoid*)0);
            glEnableVertexAttribArray(0);
            // 2nd attribute buffer : colors
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
            glBindVertexArray(0);
        }
        // Tillegg 290124: En løkke for flateobjekter
        ////////////////////////////////////////////////////////////
        for (auto it = surfaces.begin(); it != surfaces.end(); it++)
        {
            // Tilsvarende som ovenfor
                glBindVertexArray(VAO);
            for (auto it = lines.begin(); it != lines.end(); it++)
                glDrawArrays(GL_LINE_STRIP, 0, it->mVertices.size());
            for (auto it = surfaces.begin(); it != surfaces.end(); it++)
                glDrawArrays(GL_TRIANGLES, 0, it->mVertices.size());
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
}
