//
// Created by tsaury on 14/03/2022.
//

#include "glm/ext.hpp"

#include "../App.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include "Geometry.h"
#include "Camera.h"

using namespace glm;

GameObject::GameObject(App* app, int geometryIndex, int textureIndex) : EngineObject(app){

    this->geometryIndex = geometryIndex;
    this->textureIndex = textureIndex;

}

void GameObject::update(float deltaTime) {
    EngineObject::update(deltaTime);

}

void GameObject::render() const {
    mat4 modelMatrix = transform->getWorldModelMatrix();

    shared_ptr<Camera> mainCamera = app->getMainCamera();
    mat4 mvp = mainCamera->getProjectionViewMatrix() * modelMatrix;

    GLuint shaderID = app->getShaderID();

    GLuint MvpID = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(MvpID, 1, GL_FALSE, value_ptr(mvp));
    GLuint MID = glGetUniformLocation(shaderID, "M");
    glUniformMatrix4fv(MID, 1, GL_FALSE, value_ptr(modelMatrix));

    app->getTexture(textureIndex)->select(shaderID);
    app->getGeometry(geometryIndex)->draw();
}

void GameObject::fastRender() const {
    mat4 modelMatrix = transform->getWorldModelMatrix();

    shared_ptr<Camera> mainCamera = app->getMainCamera();
    mat4 mvp = mainCamera->getProjectionViewMatrix() * modelMatrix;

    GLuint shaderID = app->getShaderID();

    GLuint MvpID = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(MvpID, 1, GL_FALSE, value_ptr(mvp));
    GLuint MID = glGetUniformLocation(shaderID, "M");
    glUniformMatrix4fv(MID, 1, GL_FALSE, value_ptr(modelMatrix));

    app->getTexture(textureIndex)->select(shaderID);
    app->getGeometry(geometryIndex)->drawFast();
}

int GameObject::getGeometryIndex() const {
    return geometryIndex;
}

int GameObject::getTextureIndex() const {
    return textureIndex;
}

GameObject::ModelShaderData* GameObject::computeShaderData() {
    shaderData.M = transform->getWorldModelMatrix();
    shared_ptr<Camera> mainCamera = app->getMainCamera();
    shaderData.MVP = mainCamera->getProjectionViewMatrix() * shaderData.M;
    return &shaderData;
}