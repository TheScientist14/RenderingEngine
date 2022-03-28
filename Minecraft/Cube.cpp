//
// Created by User on 25/03/2022.
//

#include "Cube.h"
#include "../../ScriptablePipeline/App.h"
#include "../ScriptablePipeline/EngineObjects/Transform.h"

Cube::Cube(App* prmApp, shared_ptr<Geometry> prmGeometriePtr, shared_ptr<Texture> prmTexturePtr, bool prmVisibility, int prmSize) : GameObject(prmApp, prmGeometriePtr, prmTexturePtr, prmVisibility) {
    size = prmSize;
}

vec3 Cube::getLeftTopBack() {
    return vec3(transform->getPosition().x-size/2, transform->getPosition().y+size/2, transform->getPosition().z-size/2);
}