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
    orientation = quat(1,0,0,0);
    this->scaleFactor = 1;

    // TODO : should we init caches ?
}

void Transform::updateModelMatrix() {
    modelMatrix = translate(identity<mat4>(), position) * toMat4(orientation) * glm::scale(identity<mat4>(), vec3(scaleFactor));
    isModelMatrixDirty = false;
}

void Transform::updateWorldMatrix() {
    shared_ptr<EngineObject> parent = object->getParent();
    if(parent == nullptr){
        worldMatrix = getModelMatrix();
    }
    else{
        worldMatrix = object->getParent()->transform->getWorldModelMatrix() * getModelMatrix();
    }
    isWorldMatrixDirty = false;
}

void Transform::setPosition(vec3 localPosition) {
    position = localPosition;
    isModelMatrixDirty = true;
    isWorldMatrixDirty = true;
}

void Transform::setRotation(vec3 localEulerAngles) {
    setRotation(quat(vec3(radians(localEulerAngles.x), radians(localEulerAngles.y), radians(localEulerAngles.z))));
}

void Transform::setRotation(quat localOrientation) {
    orientation = localOrientation;
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

// TODO : not working properly
void Transform::rotate(vec3 eulerAnglesAdded) {
    vec3 prevEulerAngles = getEulerAngles();
    vec3 eulerAngles = prevEulerAngles + eulerAnglesAdded;
    for(int i=0; i<3; i++){
        if(eulerAngles[i] < -180){
            eulerAngles[i] += 360;
        }
        if(eulerAngles[i] > 180){
            eulerAngles[i] -= 360;
        }
    }
    setRotation(eulerAngles);
}

void Transform::rotate(quat orientationAdded) {
    orientation = orientationAdded * orientation;
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
    return modelMatrix;
}

mat4 Transform::getWorldModelMatrix() {
    if (isWorldMatrixDirty) {
        updateWorldMatrix();
    }
    return worldMatrix;
}

vec3 Transform::getForward() {
    if (isWorldMatrixDirty) {
        updateWorldMatrix();
    }
    return normalize(vec3(worldMatrix[2]));
}

vec3 Transform::getRight() {
    if (isWorldMatrixDirty) {
        updateWorldMatrix();
    }
    return normalize(vec3(worldMatrix[0]));
}

vec3 Transform::getUp() {
    if (isWorldMatrixDirty) {
        updateWorldMatrix();
    }
    return normalize(vec3(worldMatrix[1]));
}

vec3 Transform::getPosition() const {
    return position;
}

vec3 Transform::getEulerAngles() const {
    vec3 eulerAnglesRadians = eulerAngles(orientation);
    return vec3(degrees(eulerAnglesRadians.x), degrees(eulerAnglesRadians.y), degrees(eulerAnglesRadians.z));
}

quat Transform::getOrientation() const {
    return orientation;
}

float Transform::getScale() const {
    return scaleFactor;
}
