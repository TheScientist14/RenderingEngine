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

GameObject::GameObject(App* app, shared_ptr<Geometry> geometryPtr, shared_ptr<Texture> texturePtr, bool visible) : RenderedObject(app, geometryPtr, texturePtr){

    this->geometryPtr = geometryPtr;
    this->texturePtr = texturePtr;
    this->visible = visible;

}
GameObject::GameObject(App* app, shared_ptr<Geometry> geometryPtr, shared_ptr<Texture> texturePtr) : RenderedObject(app, geometryPtr, texturePtr){

    this->geometryPtr = geometryPtr;
    this->texturePtr = texturePtr;

}

void GameObject::update(int deltaTime) {
    RenderedObject::update(deltaTime);

}

//void GameObject::render() const {
//	if(visible) {
//		mat4 modelMatrix = transform->getWorldModelMatrix();
//
//		shared_ptr<Camera> mainCamera = app->getMainCamera();
//		mat4 mvp = mainCamera->getProjectionViewMatrix() * modelMatrix;
//
//		GLuint shaderID = app->getShaderID();
//
//		GLuint MvpID = glGetUniformLocation(shaderID, "MVP");
//		glUniformMatrix4fv(MvpID, 1, GL_FALSE, value_ptr(mvp));
//		GLuint MID = glGetUniformLocation(shaderID, "M");
//		glUniformMatrix4fv(MID, 1, GL_FALSE, value_ptr(modelMatrix));
//
//		app->getTexture(textureIndex)->select(shaderID);
//		app->getGeometry(geometryIndex)->draw();
//	}
//}

void GameObject::fastRender() const {
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

shared_ptr<Geometry> GameObject::getGeometryPtr() const{
    return geometryPtr;
}

shared_ptr<Texture> GameObject::getTexturePtr() const{
    return texturePtr;
}


GameObject::ModelShaderData* GameObject::computeShaderData() {
    shaderData.M = transform->getWorldModelMatrix();
    shared_ptr<Camera> mainCamera = app->getMainCamera();
    shaderData.MVP = mainCamera->getProjectionViewMatrix() * shaderData.M;
    return &shaderData;
}