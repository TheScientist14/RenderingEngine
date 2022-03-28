//
//  Character.h
//  OpenGL_Template_CPLUSPLUS
//
//  Created by Harold Serrano on 7/25/14.
//  Copyright (c) 2015 www.haroldserrano.com. All rights reserved.
//

#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/constants.hpp>
#include "EngineObject.h"

#define MAX_SHADER_LENGTH   8192

using namespace std;
using namespace glm;

class App;

class Skybox : public EngineObject {

private:

    //Cube Map Texture Object Target
    GLenum cubeMapTarget[6] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                               GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                               GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                               GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};


    GLuint textureID[16];   //Array for textures
    GLuint programObject;   //program object used to link shaders
    GLuint vertexArrayObject; //Vertex Array Object
    GLuint vertexBufferObject; //Vertex Buffer Object

    float aspect; //widthDisplay/heightDisplay ratio
    GLint modelViewProjectionUniformLocation;  //OpenGL location for our MVP uniform
    GLint normalMatrixUniformLocation;  //OpenGL location for the normal matrix
    GLint modelViewUniformLocation; //OpenGL location for the Model-View uniform
    GLint UVMapUniformLocation; //OpenGL location for the Texture Map

    //Matrices for several transformation
    mat4 projectionSpace;
    mat4 cameraViewSpace;
    mat4 modelSpace;
    mat4 worldSpace;
    mat4 modelWorldSpace;
    mat4 modelWorldViewSpace;
    mat4 modelWorldViewProjectionSpace;

    mat3 normalMatrix;

    float screenWidth;  //Width of current device display
    float screenHeight; //Height of current device display

    GLuint positionLocation; //attribute "position" location
    GLuint normalLocation;   //attribute "normal" location
    GLuint uvLocation; //attribute "uv"location

    vector<const char *> cubeMapTextures;

    unsigned char *image;
    int imageWidth, imageHeight;

    float sky_vertices[108] = {1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, 1.000000,
                               -1.000000, -1.000000, 1.000000, 1.000000, -1.000000, -1.000000, 1.000000, 0.999999,
                               -1.000001, 1.000000, 1.000000, 1.000000, -1.000000, 1.000000, 0.999999, 1.000000,
                               0.999999, -1.000001, 1.000000, 1.000000, -1.000000, -1.000000, 0.999999, -1.000001,
                               1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000, 1.000000, -1.000000,
                               1.000000, 1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, -1.000000,
                               -1.000000, 1.000000, -1.000000, -1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
                               -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000, 1.000000,
                               0.999999, 1.000000, -1.000000, 1.000000, 1.000000, 0.999999, -1.000001, 1.000000,
                               1.000000, -1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 0.999999, -1.000001,
                               1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000, -1.000000,
                               -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, 1.000000,
                               -1.000000, 1.000000, -1.000000, 1.000000, 0.999999, 1.000000, 1.000000, 1.000000,
                               -1.000000, -1.000000, 1.000000, 1.000000
    };

    int sky_index[36] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                         26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

    float angleOffset = 150;

public:
    //Skybox(App *app, std::vector<std::filesystem::path>, float uScreenWidth, float uScreenHeight);
    //Constructor
    Skybox(App *app, const char *rightImage, const char *leftImage, const char *topImage, const char *BottomImage,
           const char *frontImage, const char *backImage, float uScreenWidth, float uScreenHeight);

    ~Skybox();

    void setupOpenGL(); //Initialize the OpenGL
    void teadDownOpenGL(); //Destroys the OpenGL

    //updates the object
    void update(int deltaTime) override;
    void setTime(float dayTimePercent);

    //draws the mesh
    void draw();
};