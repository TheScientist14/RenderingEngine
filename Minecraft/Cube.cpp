//
// Created by User on 25/03/2022.
//

#include "Cube.h"
#include "../../ScriptablePipeline/App.h"
#include "../ScriptablePipeline/EngineObjects/Transform.h"
#include "../ScriptablePipeline/EngineObjects/Texture.h"
#include "../helper/ModelLoader.h"
#include "../helper/find_exe_path.h"
#include "../ScriptablePipeline/EngineObjects/Camera.h"
#include "glm/ext.hpp"

Cube::Cube(App* prmApp, int prmGeometrieIndex, int prmTextureInt, bool prmVisibility, float prmSize) : GameObject(prmApp) {
    this->texturePtr = prmApp->getTexture(prmTextureInt);
    this->geometryPtr = prmApp->getGeometry(prmGeometrieIndex);
    this->visible = prmVisibility;
    transform->setScale(prmSize);
    texturePtr->bind();
    geometryPtr->bind();
}

vec3 Cube::getLeftTopBack() {
    return vec3(transform->getPosition().x-transform->getScale()/2, transform->getPosition().y+transform->getScale()/2, transform->getPosition().z-transform->getScale()/2);
}

void Cube::fastRender() const {
    if(visible) {
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
}