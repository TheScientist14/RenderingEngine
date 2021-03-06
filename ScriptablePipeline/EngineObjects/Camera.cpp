//
// Created by tsaury on 14/03/2022.
//

#include "Camera.h"

#include <GL/glew.h>
#include "glm/ext.hpp"

#include "../App.h"
#include "Transform.h"

Camera::Camera(App *app) : Camera(app, 1024, 768, false, 45, 0.1f, 1000.0f) {

}

Camera::Camera(App *app, int width, int height, bool isOrtho, float fieldOfView, float nearPlane, float farPlane)
        : EngineObject(app) {

    this->width = width;
    this->height = height;
    this->isOrtho = isOrtho;
    this->fieldOfView = fieldOfView;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;

    this->transform->setPosition(vec3(0, 0, 10));

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
}

Camera::~Camera() {

}

mat4 Camera::getViewMatrix() {

    mat4 view = inverse(transform->getModelMatrix());


    return view;
}

mat4 Camera::getProjectionMatrix() {

    mat4 projection;
    if (isOrtho) {
        projection = ortho(((float) -width) / 2000, ((float) width) / 2000, ((float) -height) / 2000,
                           ((float) height) / 2000, nearPlane, farPlane); // In world coordinates

    } else {
        projection = perspective(radians(fieldOfView), (float) width / (float) height, nearPlane, farPlane);
    }

    return projection;

}

mat4 Camera::getProjectionViewMatrix() {
    return getProjectionMatrix() * getViewMatrix();
}

void Camera::update(int deltaTime) {
    EngineObject::update(deltaTime);

    glClearColor(0.5, 0.5, 0.5, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint VID = glGetUniformLocation(app->getShaderID(), "V");
    glUniformMatrix4fv(VID, 1, GL_FALSE, value_ptr(getViewMatrix()));

    if (isWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}