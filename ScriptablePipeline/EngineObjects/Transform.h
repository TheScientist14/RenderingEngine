//
// Created by tsaury on 14/03/2022.
//
#pragma once

#include <memory>

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include <glm/gtc/quaternion.hpp>

using namespace std;
using namespace glm;

class EngineObject;

class Transform {

protected:
    vec3 position;
    quat orientation;
    float scaleFactor;

    // caches
    bool isModelMatrixDirty = true;
    mat4 modelMatrix;
    bool isWorldMatrixDirty = true;
    mat4 worldMatrix;

    void updateModelMatrix();
    void updateWorldMatrix();

public:
    const EngineObject* object;

    Transform(const EngineObject* object);

    mat4 getModelMatrix();
    mat4 getWorldModelMatrix();
    vec3 getForward();
    vec3 getRight();
    vec3 getUp();
    vec3 getPosition() const;
    vec3 getEulerAngles() const;
    quat getOrientation() const;
    float getScale() const;

    void setPosition(vec3 localPosition);
    void setRotation(vec3 localEulerAngles);
    void setRotation(quat localOrientation);
    void setScale(float localScaleFactor);

    void move(vec3 positionOffset);
    __declspec(deprecated) void rotate(vec3 eulerAngles);
    void rotate(quat orientationAdded);
    void scale(float scaleFactor);

    void setWorldPosition(vec3 worldPosition);
    void setWorldRotation(vec3 worldEulerAngles);
    void setWorldRotation(quat worldOrientation);
    void setWorldScale(float worldScale);

    void setWorldMatrixIsDirty(bool isDirty);
};
