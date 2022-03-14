//
// Created by tsaury on 14/03/2022.
//
#pragma once
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

using namespace glm;

class Transform {

public:
    vec3 position;
    vec3 rotation;
    vec3 scale;

    mat4 getModelMatrix();

};
