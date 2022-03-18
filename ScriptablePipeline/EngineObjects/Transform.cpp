//
// Created by tsaury on 14/03/2022.
//

#include "glm/ext.hpp"

#include "Transform.h"

Transform::Transform() {
    this->position = vec3(0, 0, 0);
    this->rotation = vec3(0, 0, 0);
    this->scale = vec3(1, 1, 1);
}

mat4 Transform::getRotationMatrix(){
    mat4 identity = glm::identity<mat4>();
    mat4 rotateMatZ = rotate(identity, radians(rotation.z), vec3(0.0f,0.0f,1.0f));
    vec4 yAxis = rotateMatZ * vec4(0, 1, 0, 1);
    mat4 rotateMatY = rotate(identity, radians(rotation.y), vec3(yAxis));
    vec4 xAxis = rotateMatY * rotateMatZ  * vec4(1, 0, 0, 1);
    mat4 rotateMatX = rotate(identity, radians(rotation.x), vec3(xAxis));
    return rotateMatX * rotateMatY * rotateMatZ;
}

mat4 Transform::getModelMatrix() {

    mat4 identity = glm::identity<mat4>();

    mat4 scaleMat = glm::scale(identity, scale);

    mat4 rotateMatZ = rotate(identity, radians(rotation.z), vec3(0.0f,0.0f,1.0f));
    vec4 yAxis = rotateMatZ * vec4(0, 1, 0, 1);
    mat4 rotateMatY = rotate(identity, radians(rotation.y), vec3(yAxis));
    vec4 xAxis = rotateMatY * rotateMatZ  * vec4(1, 0, 0, 1);
    mat4 rotateMatX = rotate(identity, radians(rotation.x), vec3(xAxis));

    mat4 translateMat = translate(identity, position);

    return translateMat * rotateMatX * rotateMatY * rotateMatZ * scaleMat;

}

vec3 Transform::getForward(){
    return getRotationMatrix() * vec4(0,0,1,0);
}

vec3 Transform::getRight(){
    return getRotationMatrix() * vec4(1,0,0,0);
}

vec3 Transform::getUp(){
    return getRotationMatrix() * vec4(0,1,0,0);
}