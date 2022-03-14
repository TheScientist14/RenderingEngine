//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

#include "EngineObject.h"

using namespace glm;

class Camera : public EngineObject{
public:
    Camera(App* app, int width, int height, bool isOrtho, float fieldOfView, float nearPlane, float farPlane);
    Camera(App* app);
    virtual ~Camera();

    mat4 getViewMatrix();
    mat4 getProjectionMatrix();
    mat4 getProjectionViewMatrix();

protected:
    int width = 1024;
    int height = 768;
    bool isOrtho = false;
    float fieldOfView = 90;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
};

