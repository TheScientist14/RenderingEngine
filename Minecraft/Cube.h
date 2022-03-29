//
// Created by avarnier-navarro on 25/03/2022.
//

#pragma once

#include "../ScriptablePipeline/EngineObjects/GameObject.h"

class Cube : public GameObject{

public:

    Cube(App* prmApp, int prmGeometrieIndex, int prmTextureIndex, bool prmVisibility, int prmSize);
    vec3 getLeftTopBack();

protected:
    int size;

    void fastRender() const override;
};
