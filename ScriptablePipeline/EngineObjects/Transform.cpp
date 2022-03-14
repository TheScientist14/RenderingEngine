//
// Created by tsaury on 14/03/2022.
//
#include "Transform.h"
#include "glm/ext.hpp"

mat4 Transform::getModelMatrix() {

    mat4 model = glm::identity<mat4>();

    model = glm::scale(model,scale);

    model = glm::rotate(model, radians(rotation.x), vec3(1.0f,0.0f,0.0f));
    model = glm::rotate(model, radians(rotation.y), vec3(0.0f,1.0f,0.0f));
    model = glm::rotate(model, radians(rotation.z), vec3(0.0f,0.0f,1.0f));

    model = glm::translate(model, position);

    return model;

}




