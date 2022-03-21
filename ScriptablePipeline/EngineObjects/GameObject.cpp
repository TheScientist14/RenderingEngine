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

    mat4 modelMatrix = transform->getModelMatrix();
    shared_ptr<EngineObject> parentCursor = parent;
    while(parentCursor.get() != nullptr){
        modelMatrix = parentCursor->transform->getModelMatrix() * modelMatrix;
        parentCursor = parentCursor->getParent();
    }

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
