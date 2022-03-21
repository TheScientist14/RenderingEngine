//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include "EngineObject.h"
#include "GL/glew.h"

class GameObject : public EngineObject{

protected:
    int geometryIndex;
    int textureIndex;

public:
    GameObject(App* app, int geometryIndex, int textureIndex);

protected:

    void update(float deltaTime) override;

};
