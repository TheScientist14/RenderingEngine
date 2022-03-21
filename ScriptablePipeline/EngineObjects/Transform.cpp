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
    if(prevRotation == rotation){
        return prevRotationMatrix;
    }else{
        // TODO improve rotation computation
        mat4 identity = glm::identity<mat4>();

        mat4 rotateMatZ = rotate(identity, radians(rotation.z), vec3(0.0f,0.0f,1.0f));
        vec4 yAxis = rotateMatZ * vec4(0, 1, 0, 1);
        mat4 rotateMatY = rotate(identity, radians(rotation.y), vec3(yAxis));
        vec4 xAxis = rotateMatY * rotateMatZ  * vec4(1, 0, 0, 1);
        mat4 rotateMatX = rotate(identity, radians(rotation.x), vec3(xAxis));

        return rotateMatX * rotateMatY * rotateMatZ;
    }
}

mat4 Transform::getModelMatrix() {
    if(prevPosition == position && prevRotation == rotation && prevScale == scale){
        return prevModelMatrix;
    }
    else{
        mat4 identity = glm::identity<mat4>();

        mat4 scaleMat = glm::scale(identity, scale);
        mat4 rotationMat = getRotationMatrix();
        mat4 translateMat = translate(identity, position);

        return translateMat * rotationMat * scaleMat;
    }
}

vec3 Transform::getForward(){
    if(prevRotationForward == rotation){
        return prevForward;
    }else{
        prevForward = getRotationMatrix() * vec4(0,0,1,0);
        prevRotationForward = rotation;
        return prevForward;
    }
}

vec3 Transform::getRight(){
    if(prevRotationRight == rotation){
        return prevRight;
    }else{
        prevRight = getRotationMatrix() * vec4(1,0,0,0);
        prevRotationRight = rotation;
        return prevRight;
    }
}

vec3 Transform::getUp(){
    if(prevRotationUp == rotation){
        return prevUp;
    }else{
        prevUp = getRotationMatrix() * vec4(0,1,0,0);
        prevRotationUp = rotation;
        return prevUp;
    }
}