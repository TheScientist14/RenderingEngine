//
// Created by tsaury on 11/03/2022.
//

#include "AppCube.h"

#include <string>

#include "SDL.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <gl/GL.h>
#include "../helper/stb_image.h"
#include "../Shaders/loadShader.h"

using namespace std;
using namespace glm;

void AppCube::gl_init(){

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
#pragma region cube_vertex
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };
#pragma endregion cube_vertex

#pragma region tetrahedron_vertex

    static const GLfloat g_tetrahedron_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : base
            -1.0f,-1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, // triangle 1 : end
            -1.0f,-1.0f,-1.0f,// triangle 2 : base
            1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            0.0, 1.0, 0.0, // triangle 3 : 1st face
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
            0.0, 1.0, 0.0, // triangle 4 : 2nd face
            -1.0f,-1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            0.0, 1.0, 0.0, // triangle 5 : 3rd face
            1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            0.0, 1.0, 0.0, // triangle 6 : 4th face
            1.0f, -1.0f, -1.0f,
            -1.0f,-1.0f,-1.0f,
    };

#pragma endregion tetrahedron_vertex

    // One color for each vertex. They were generated randomly.
#pragma region color_buffer
    static const GLfloat g_color_buffer_data[] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
    };
#pragma endregion color_buffer

#pragma region UV_buffer

    // Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
    static const GLfloat g_uv_buffer_data[] = {
            0.000059f, 1.0f-0.000004f,
            0.000103f, 1.0f-0.336048f,
            0.335973f, 1.0f-0.335903f,
            1.000023f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.336024f, 1.0f-0.671877f,
            0.667969f, 1.0f-0.671889f,
            1.000023f, 1.0f-0.000013f,
            0.668104f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.000059f, 1.0f-0.000004f,
            0.335973f, 1.0f-0.335903f,
            0.336098f, 1.0f-0.000071f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.336024f, 1.0f-0.671877f,
            1.000004f, 1.0f-0.671847f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.668104f, 1.0f-0.000013f,
            0.335973f, 1.0f-0.335903f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.668104f, 1.0f-0.000013f,
            0.336098f, 1.0f-0.000071f,
            0.000103f, 1.0f-0.336048f,
            0.000004f, 1.0f-0.671870f,
            0.336024f, 1.0f-0.671877f,
            0.000103f, 1.0f-0.336048f,
            0.336024f, 1.0f-0.671877f,
            0.335973f, 1.0f-0.335903f,
            0.667969f, 1.0f-0.671889f,
            1.000004f, 1.0f-0.671847f,
            0.667979f, 1.0f-0.335851f
    };

#pragma endregion UV_buffer

    glGenVertexArrays(1, &cube_arrayid);
    glBindVertexArray(cube_arrayid);
    // This will identify our vertex buffer

    // Generate 1 buffer, put the resulting identifier in cube_vertexbuffer
    glGenBuffers(1, &cube_vertexbuffer);

    // The following commands will talk about our 'cube_vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, cube_vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    //color
    glGenBuffers(1, &cube_colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, cube_colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
//    glGenVertexArrays(1, &tetra_arrayid);
//    glBindVertexArray(tetra_arrayid);
//    //vertex tetra
//    glGenBuffers(1, &tetra_vertexbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, tetra_vertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_tetrahedron_vertex_buffer_data), g_tetrahedron_vertex_buffer_data, GL_STATIC_DRAW);
//    //color tetra
//    glGenBuffers(1, &tetra_colorbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, tetra_colorbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // Create and compile our GLSL program from the shaders
    programID = loadShader::LoadShaders( "/Shaders/ColoredCube.vertexshader" , "/Shaders/ColoredCube.fragmentshader" );
}

void AppCube::main_loop() {
    glClearColor(0, 0, 0.4, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);
    // Draw triangle...
    // 1rst attribute buffer : vertices

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    mat4 Projection = perspective(radians(120.0f), (float)width / (float)height, 0.1f, 100.0f);
    //glm::mat4 Projection = ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    mat4 View = lookAt(
            vec3(4,3,3), // Camera is at (4,3,3), in World Space
            vec3(0,0,0), // and looks at the origin
            vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    mat4 Model = mat4(1.0f);
    mat4 mvp = Projection * View * Model;
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value_ptr(mvp));

    glEnableVertexAttribArray(0);
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, cube_vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );
    glBindBuffer(GL_ARRAY_BUFFER, cube_colorbuffer);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );
       int width, height, channel;
    stbi_uc *img = stbi_load("../Images/uvtemplate.bmp", &width, &height, &channel, 0);

    GLuint textureID;
    //glGenTextures(1, reinterpret_cast<GLuint *>(img));
    glGenTextures(1, &textureID);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    unsigned char * data;

    data = new unsigned char [512*512*3];
// Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glVertexAttribPointer(
            2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
//    glBindBuffer(GL_ARRAY_BUFFER, tetra_vertexbuffer);
//    glVertexAttribPointer(
//            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//            3,                  // size
//            GL_FLOAT,           // type
//            GL_FALSE,           // normalized?
//            0,                  // stride
//            (void*)0            // array buffer offset
//    );
//    Model = mat4(1.0f);
//    Model = translate(Model, vec3(0, 3, 0));
//    mvp = Projection * View * Model;
//    MatrixID = glGetUniformLocation(programID, "MVP");
//    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, value_ptr(mvp));
    //glDrawArrays(GL_TRIANGLES, 0, 6*3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void AppCube::clean(){
    // Cleanup VBO
    glDeleteBuffers(1, &cube_vertexbuffer);
    glDeleteBuffers(1, &cube_colorbuffer);
    glDeleteVertexArrays(1, &cube_arrayid);
    glDeleteBuffers(1, &tetra_vertexbuffer);
    glDeleteBuffers(1, &tetra_colorbuffer);
    glDeleteVertexArrays(1, &tetra_arrayid);
    glDeleteProgram(programID);

    SDL_DestroyWindow(win);
}

void AppCube::loadTexture(){
    int width, height, channel;
    stbi_uc *img = stbi_load("../Images/uvtemplate.bmp", &width, &height, &channel, 0);
}