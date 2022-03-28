//
//  Character.mm
//  OpenGL_Template_CPLUSPLUS
//
//  Created by Harold Serrano on 7/25/14.
//  Copyright (c) 2015 www.haroldserrano.com. All rights reserved.
//

#include "Skybox.h"
#include <vector>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <../../helper/stb_image.h>
#include <../../Shaders/loadShader.h>
#include "Transform.h"
#include "../App.h"
#include "Camera.h"

static GLubyte shaderText[MAX_SHADER_LENGTH];

Skybox::Skybox(App *app, const char *rightImage, const char *leftImage, const char *topImage, const char *BottomImage,
               const char *frontImage, const char *backImage, float uScreenWidth, float uScreenHeight) : EngineObject(
        app) {

    //1. load each texture image reference into a vector
    cubeMapTextures.push_back(rightImage);
    cubeMapTextures.push_back(leftImage);
    cubeMapTextures.push_back(topImage);
    cubeMapTextures.push_back(BottomImage);
    cubeMapTextures.push_back(frontImage);
    cubeMapTextures.push_back(backImage);

    //2. set the width and heigh of the device
    screenWidth = uScreenWidth;
    screenHeight = uScreenHeight;

    //3. Enable Depth Testing
    glEnable(GL_DEPTH_TEST);

    transform->scale(1000);
    transform->setRotation(vec3(0,0,angleOffset));

}

void Skybox::setupOpenGL() {

    //load the shaders, compile them and link them

    //loadShaders("SkyShader.vsh", "SkyShader.fsh");
    programObject = loadShader::LoadShaders("/Shaders/SkyboxShader.vertexshader",
                                            "/Shaders/SkyboxShader.fragmentshader");

    glUseProgram(programObject);

    //1. Generate a Vertex Array Object

    glGenVertexArrays(1, &vertexArrayObject);

    //2. Bind the Vertex Array Object

    glBindVertexArray(vertexArrayObject);

    //3. Generate a Vertex Buffer Object

    glGenBuffers(1, &vertexBufferObject);

    //4. Bind the Vertex Buffer Object

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    //5. Dump the data into the Buffer
    /* Read "Loading data into OpenGL Buffers" if not familiar with loading data
    using glBufferSubData.
    http://www.www.haroldserrano.com/blog/loading-vertex-normal-and-uv-data-onto-opengl-buffers
    */

    glBufferData(GL_ARRAY_BUFFER, sizeof(sky_vertices), NULL, GL_STATIC_DRAW);

    //5a. Load vertex data with glBufferSubData
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sky_vertices), sky_vertices);


    //6. Get the location of the shader attribute called "position"

    positionLocation = glGetAttribLocation(programObject, "position");


    //8. Enable attribute locations

    //8a. Enable the position attribute
    glEnableVertexAttribArray(positionLocation);

    //9. Link the buffer data to the shader attribute locations

    //9a. Link the buffer data to the shader's position location
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) 0);


    //10. Get Location of uniform
    modelViewProjectionUniformLocation = glGetUniformLocation(programObject, "modelViewProjectionMatrix");


    /*Since we are going to start the rendering process by using glDrawElements
     We are going to create a buffer for the indices. Read "Starting the rendering process in OpenGL"
     if not familiar. http://www.www.haroldserrano.com/blog/starting-the-primitive-rendering-process-in-opengl */

    //11. Create a new buffer for the indices
    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);

    //12. Bind the new buffer to binding point GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

    //13. Load the buffer with the indices found in smallHouse1_index array
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sky_index), sky_index, GL_STATIC_DRAW);


    //14. Activate GL_TEXTURE0
    glActiveTexture(GL_TEXTURE0);

    //15.a Generate a texture buffer
    glGenTextures(1, &textureID[0]);

    //16. Bind texture0
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);

    //17. Simple For loop to get each image reference

    for (int i = 0; i < cubeMapTextures.size(); i++) {

        //17a.Decode each cube map image into its raw image data.
        //if(convertImageToRawImage(cubeMapTextures.at(i))){

        image = stbi_load(cubeMapTextures.at(i), &imageWidth, &imageHeight, nullptr, 0);

        //17b. if decompression was successful, set the texture parameters

        if (image) {
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            //17c. load the image data into the current bound texture buffer
            //cubeMapTarget[] contains the cube map targets
            glTexImage2D(cubeMapTarget[i], 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         image);

            stbi_image_free(image);
        } else {
            printf("Couldn't load %s\n", cubeMapTextures.at(i));
        }
    }

    //18. Get the location of the Uniform Sampler2D
    UVMapUniformLocation = glGetUniformLocation(programObject, "SkyboxTexture");

    //19. Unbind the VAO
    glBindVertexArray(0);
    transform->scale(10);

    update(0);
}

void Skybox::update(int deltaTime) {

    Sp_Camera camera = app->getMainCamera();
    glUseProgram(programObject);

    float deltaRot = deltaTime / 360.0f;
    transform->rotate(angleAxis(radians(deltaRot), vec3(0, 0, 1)));
    transform->setPosition(camera->transform->getPosition());

    modelWorldViewProjectionSpace = camera->getProjectionViewMatrix() * transform->getWorldModelMatrix();

    //5. Assign the model-world-view-projection matrix data to the uniform location:modelviewProjectionUniformLocation
    glUniformMatrix4fv(modelViewProjectionUniformLocation, 1, GL_FALSE, value_ptr(modelWorldViewProjectionSpace));

}

void Skybox::setTime(float dayTimePercent) {

    Sp_Camera camera = app->getMainCamera();
    glUseProgram(programObject);

    transform->setRotation(vec3(0, 0, angleOffset + dayTimePercent * 360.0f));

    modelWorldViewProjectionSpace = camera->getProjectionViewMatrix() * transform->getWorldModelMatrix();

    //5. Assign the model-world-view-projection matrix data to the uniform location:modelviewProjectionUniformLocation
    glUniformMatrix4fv(modelViewProjectionUniformLocation, 1, GL_FALSE, value_ptr(modelWorldViewProjectionSpace));
}

void Skybox::draw() {


    //1. Set the shader program
    glUseProgram(programObject);

    //2. Bind the VAO
    glBindVertexArray(vertexArrayObject);

    //3. Activate the texture unit
    glActiveTexture(GL_TEXTURE0);

    //4 Bind the texture object
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);

    //5. Specify the value of the UV Map uniform
    glUniform1i(UVMapUniformLocation, 0);

    //6. draw the pixels if the incoming depth value is less than or equal to the stored depth value.
    glDepthFunc(GL_LEQUAL);

    //7. Start the rendering process
    glDrawElements(GL_TRIANGLES, sizeof(sky_index) / 4, GL_UNSIGNED_INT, (void *) 0);


    //8. draw the pixels if the incoming depth value is less than the stored depth value
    glDepthFunc(GL_LESS);

    //9. Disable the VAO
    glBindVertexArray(0);

}

void Skybox::teadDownOpenGL() {

    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteVertexArrays(1, &vertexArrayObject);


    if (programObject) {
        glDeleteProgram(programObject);
        programObject = 0;

    }

}

Skybox::~Skybox() {
    teadDownOpenGL();
}
