//
// Created by tsaury on 14/03/2022.
//
#pragma once

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

#include "EngineObject.h"

using namespace glm;

class Transform {

public:
    vec3 position;
    vec3 rotation;
    vec3 scale;

    vec3 prevPosition;
    vec3 prevRotation;
    vec3 prevScale;
    mat4 prevRotationMatrix;
    mat4 prevModelMatrix;
    vec3 prevRotationForward;
    vec3 prevForward;
    vec3 prevRotationRight;
    vec3 prevRight;
    vec3 prevRotationUp;
    vec3 prevUp;

    Transform();

    mat4 getRotationMatrix();
    mat4 getModelMatrix();
    vec3 getForward();
    vec3 getRight();
    vec3 getUp();

};
