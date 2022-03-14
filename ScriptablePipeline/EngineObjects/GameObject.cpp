//
// Created by tsaury on 14/03/2022.
//

#include "GameObject.h"
#include "../App.h"
#include "glm/ext.hpp"

using namespace glm;

GameObject::GameObject(App* app, int geometryIndex, int textureIndex) : EngineObject(app){

    this->geometryIndex = geometryIndex;
    this->textureIndex = textureIndex;

}

void GameObject::update(float deltaTime) {
    EngineObject::update(deltaTime);

    mat4 mvp = app->getMainCamera()->getProjectionViewMatrix() * transform.getModelMatrix();

    GLuint shaderID = app->getShaderID();

    app->getTexture(textureIndex)->select(shaderID);
    app->getGeometry(geometryIndex)->draw(shaderID);

    GLuint MatrixID = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(mvp));

}
