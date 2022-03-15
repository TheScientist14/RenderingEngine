//
// Created by tsaury on 14/03/2022.
//
#include "Transform.h"
#include "glm/ext.hpp"

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




