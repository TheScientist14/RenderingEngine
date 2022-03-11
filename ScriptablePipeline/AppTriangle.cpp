//
// Created by tsaury on 11/03/2022.
//

#include "AppTriangle.h"

#include <string>

#include "SDL.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <gl/GL.h>
#include "../Shaders/loadShader.h"

using namespace std;
using namespace glm;

void AppTriangle::gl_init(){

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

    // This will identify our vertex buffer

// Generate 1 buffer, put the resulting identifier in cube_vertexbuffer
    glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'cube_vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Create and compile our GLSL program from the shaders
    programID = loadShader::LoadShaders( "/Shaders/TransformTriangle.vertexshader" , "/Shaders/SimpleFragmentShader.fragmentshader" );
    //programID = loadShader::LoadShaders( "D:\\Users\\tsaury\\RenderingEngine\\Shaders\\SimpleVertexShader.vertexshader" , "D:\\Users\\tsaury\\RenderingEngine\\Shaders\\SimpleFragmentShader.fragmentshader" );

}

void AppTriangle::main_loop() {
    glClearColor(0, 0, 0.4, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Use our shader
    glUseProgram(programID);
    // 1rst attribute buffer : vertices
    mat4 Projection = perspective(radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    //mat4 Projection = ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    mat4 View = lookAt(
            vec3(4,3,3), // Camera is at (4,3,3), in World Space
            vec3(0,0,0), // and looks at the origin
            vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    mat4 Model = mat4(1.0f);
    vec3 YAxis = vec3(0.0f,1.0f,0.0f);
    //Model = rotate(Model, radians(180.0f), YAxis);
    mat4 mvp = Projection * View * Model;
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value_ptr(mvp));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );
    // Draw triangle...
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

}

void AppTriangle::clean(){
    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    SDL_DestroyWindow(win);
}
