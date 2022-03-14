//
// Created by tsaury on 14/03/2022.
//

#include "EngineObject.h"

EngineObject::EngineObject(App* app) {

    this->app = app;

    this->transform.position = vec3(0, 0, 0);
    this->transform.rotation = vec3(0, 0, 0);
    this->transform.scale = vec3(1, 1, 1);

}

EngineObject::~EngineObject() {

}

void EngineObject::update(float deltaTime) {

}
