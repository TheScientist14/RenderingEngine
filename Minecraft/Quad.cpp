//
// Created by avarnier-navarro on 28/03/2022.
//

#include "Quad.h"
#include "../ScriptablePipeline/EngineObjects/Transform.h"
#include "../ScriptablePipeline/EngineObjects/Geometry.h"
#include "../ScriptablePipeline/EngineObjects/Texture.h"
#include "../ScriptablePipeline/EngineObjects/Camera.h"
#include "../ScriptablePipeline/App.h"
#include "glm/ext.hpp"

Quad::Quad(App *app, int height, int width, vec3 direction) : RenderedObject(app, nullptr, nullptr) {

    shared_ptr<Texture> cube_texture = make_shared<Texture>("../Images/dirt.bmp");
    this->direction = direction;
    this->height = height;
    this->width = width;
    this->texturePtr = cube_texture;
    triangles.insert(triangles.end(), {0, 1, 2, 1, 2, 3});
    int x = direction.x;
    int y = direction.y;

    if (x != 0) {
        createTrianglesX();
    } else if (y != 0) {
        createTrianglesY();
    } else {
        createTrianglesZ();
    }
}

vector<unsigned int> Quad::getTriangles() {
    return triangles;
}

void Quad::createTrianglesZ() {
    float x = transform->getPosition().x;
    float y = transform->getPosition().y;
    float z = transform->getPosition().z;

    trianglesPos.insert(trianglesPos.end(), {x, y, z,
                                             x + width, y, z,
                                             x, y - height, z,
                                             x + width, y - height, z});

    uvVector.insert(uvVector.end(), {0, 0, 0, (float)height, (float)width, (float)height, (float)width, 0});

    normalsVector.insert(normalsVector.end(), {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0});


    this->geometryPtr = make_shared<Geometry>(getTrianglesPos().data(), getNormalsVector().data(), getUVVector().data(),
                                              4, getTriangles().data(), 2);
    texturePtr->bind();
    geometryPtr->bind();
}

void Quad::createTrianglesY() {

    float x = transform->getPosition().x;
    float y = transform->getPosition().y;
    float z = transform->getPosition().z;

    trianglesPos.insert(trianglesPos.end(), {x, y, z,
                                             x + height, y, z,
                                             x, y, z + width,
                                             x + height, y, z + width});


    uvVector.insert(uvVector.end(), {0, 0, 0, (float)height, (float)width, (float)height, (float)width, 0});

    normalsVector.insert(normalsVector.end(), {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0});


    this->geometryPtr = make_shared<Geometry>(getTrianglesPos().data(), getNormalsVector().data(), getUVVector().data(),
                                              4, getTriangles().data(), 2);
    texturePtr->bind();
    geometryPtr->bind();
}

void Quad::createTrianglesX() {

    float x = transform->getPosition().x;
    float y = transform->getPosition().y;
    float z = transform->getPosition().z;

    trianglesPos.insert(trianglesPos.end(), {x, y - height, z,
                                             x, y, z,
                                             x, y - height, z + width,
                                             x, y, z + width});



    uvVector.insert(uvVector.end(), {0, 0, 0, (float)height, (float)width, (float)height, (float)width, 0});

    normalsVector.insert(normalsVector.end(), {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1});


    this->geometryPtr = make_shared<Geometry>(getTrianglesPos().data(), getNormalsVector().data(), getUVVector().data(),
                                              4, getTriangles().data(), 2);
    texturePtr->bind();
    geometryPtr->bind();
}

vector<float> Quad::getTrianglesPos() {
    return trianglesPos;
}

shared_ptr<Geometry> Quad::getGeometryPtr() {
    return geometryPtr;
}

vector<float> Quad::getUVVector() {
    return uvVector;
}

vector<float> Quad::getNormalsVector() {
    return normalsVector;
}

void Quad::fastRender() const {
    mat4 modelMatrix = transform->getWorldModelMatrix();

    shared_ptr<Camera> mainCamera = app->getMainCamera();
    mat4 mvp = mainCamera->getProjectionViewMatrix() * modelMatrix;

    GLuint shaderID = app->getShaderID();

    GLuint MvpID = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(MvpID, 1, GL_FALSE, value_ptr(mvp));
    GLuint MID = glGetUniformLocation(shaderID, "M");
    glUniformMatrix4fv(MID, 1, GL_FALSE, value_ptr(modelMatrix));

    texturePtr->select(shaderID);
    geometryPtr->drawFast();


}
