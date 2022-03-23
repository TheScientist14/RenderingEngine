//
// Created by tsaury on 14/03/2022.
//

#include "glm/ext.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Transform.h"
#include "EngineObject.h"

Transform::Transform(const EngineObject *object) {
    this->object = object;

    this->position = vec3(0, 0, 0);
    orientation = quat();
    this->scaleFactor = 1;

    // TODO : should we init caches ?
}

void Transform::updateModelMatrix() {
    prevModelMatrix = translate(identity<mat4>(), position) * toMat4(orientation) * glm::scale(identity<mat4>(), vec3(scaleFactor));
    isModelMatrixDirty = false;
}

void Transform::updateWorldMatrix() {
    shared_ptr<EngineObject> parent = object->getParent();
    if(parent == nullptr){
        prevWorldMatrix = getModelMatrix();
    }
    else{
        prevWorldMatrix = object->getParent()->transform->getWorldModelMatrix() * getModelMatrix();
    }
    isWorldMatrixDirty = false;
}

void Transform::setPosition(vec3 localPosition) {
    position = localPosition;
    isModelMatrixDirty = true;
    isWorldMatrixDirty = true;
}

void Transform::setRotation(vec3 localEulerAngles) {
    orientation = quat(localEulerAngles);
    isModelMatrixDirty = true;
    isWorldMatrixDirty = true;
}

void Transform::setScale(float localScaleFactor) {
    scaleFactor = localScaleFactor;
    isModelMatrixDirty = true;
    isWorldMatrixDirty = true;
}

void Transform::move(vec3 positionOffset) {
    position += positionOffset;
    isModelMatrixDirty = true;
    isWorldMatrixDirty = true;
}

void Transform::rotate(vec3 eulerAngles) {
    orientation *= quat(eulerAngles);
    isModelMatrixDirty = true;
    isWorldMatrixDirty = true;
}

void Transform::scale(float scaleFactor) {
    this->scaleFactor *= scaleFactor;
    isModelMatrixDirty = true;
    isWorldMatrixDirty = true;
}

void Transform::setWorldPosition(vec3 worldPosition) {
    // TODO
}

void Transform::setWorldRotation(vec3 worldRotation) {
    // TODO
}

void Transform::setWorldScale(float worldScale) {
    // TODO
}

void Transform::setWorldMatrixIsDirty(bool isDirty) {
    isWorldMatrixDirty = true;
}

mat4 Transform::getModelMatrix() {
    if (isModelMatrixDirty) {
        updateModelMatrix();
    }
    return prevModelMatrix;
}

mat4 Transform::getWorldModelMatrix() {
    if (isWorldMatrixDirty) {
        updateWorldMatrix();
    }
    return prevWorldMatrix;
}

vec3 Transform::getForward() {
    if (isWorldMatrixDirty) {
        updateWorldMatrix();
    }
    return normalize(vec3(prevWorldMatrix[2]));
}

vec3 Transform::getRight() {
    if (isWorldMatrixDirty) {
        updateWorldMatrix();
    }
    return normalize(vec3(prevWorldMatrix[0]));
}

vec3 Transform::getUp() {
    if (isWorldMatrixDirty) {
        updateWorldMatrix();
    }
    return normalize(vec3(prevWorldMatrix[1]));
}

vec3 Transform::getPosition() const {
    return position;
}

vec3 Transform::getEulerAngles() const {
    return eulerAngles(orientation);
}

float Transform::getScale() const {
    return scaleFactor;
}
