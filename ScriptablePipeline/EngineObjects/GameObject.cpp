//
// Created by tsaury on 14/03/2022.
//

#include "glm/ext.hpp"

#include "../App.h"
#include "GameObject.h"
#include "Transform.h"

using namespace glm;

GameObject::GameObject(App* app, int geometryIndex, int textureIndex) : EngineObject(app){

    this->geometryIndex = geometryIndex;
    this->textureIndex = textureIndex;

}

void GameObject::update(float deltaTime) {
    EngineObject::update(deltaTime);

    mat4 modelMatrix = transform->getModelMatrix();
    shared_ptr<EngineObject> parentCursor = parent;
    while(parentCursor.get() != nullptr){
        modelMatrix = parentCursor->transform->getModelMatrix() * modelMatrix;
        parentCursor = parentCursor->getParent();
    }

    mat4 mvp = app->getMainCamera()->getProjectionViewMatrix() * modelMatrix;

    GLuint shaderID = app->getShaderID();

    GLuint MatrixID = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(mvp));

    app->getTexture(textureIndex)->select(shaderID);
    app->getGeometry(geometryIndex)->draw(shaderID);

}
