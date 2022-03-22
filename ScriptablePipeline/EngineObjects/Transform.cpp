//
// Created by tsaury on 14/03/2022.
//

#include "glm/ext.hpp"

#include "Transform.h"
#include "EngineObject.h"

Transform::Transform(const EngineObject *object) {
    this->object = object;

    this->position = vec3(0, 0, 0);
    this->eulerAngles = vec3(0, 0, 0);
    this->scaleFactor = 1;

    // TODO : should we init caches ?
}

// see https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2012/07/euler-angles1.pdf for details on euler angles to rotation matrix
void Transform::updateModelMatrix() {
    float c1 = cos(eulerAngles.x);
    float s1 = sin(eulerAngles.x);
    float c2 = cos(eulerAngles.y);
    float s2 = sin(eulerAngles.y);
    float c3 = cos(eulerAngles.z);
    float s3 = sin(eulerAngles.z);
    prevModelMatrix = mat4(
            scaleFactor * c2 * c3,                  scaleFactor * c2 * s3,                  scaleFactor * (-s2),   position.x,
            scaleFactor * (s1 * s2 * c3 - c1 * s3), scaleFactor * (s1 * s2 * s3 + c1 * c3), scaleFactor * s1 * c1, position.y,
            scaleFactor * (c1 * s2 * c3 + s1 * s3), scaleFactor * (c1 * s2 * s3 - s1 * c3), scaleFactor * c1 * c2, position.z,
            0,                      0,                      0,       1
    );
    isModelMatrixDirty = false;
}

void Transform::updateWorldMatrix() {
    prevWorldMatrix = object->getParent()->transform->getWorldModelMatrix() * getModelMatrix();
    isWorldMatrixDirty = false;
}

void Transform::setPosition(vec3 localPosition) {
    position = localPosition;
    isModelMatrixDirty = true;
    isWorldMatrixDirty = true;
}

void Transform::setRotation(vec3 localEulerAngles) {
    eulerAngles = localEulerAngles;
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
    this->eulerAngles += eulerAngles;
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
    } else {
        return prevModelMatrix;
    }
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
    return eulerAngles;
}

float Transform::getScale() const {
    return scaleFactor;
}
