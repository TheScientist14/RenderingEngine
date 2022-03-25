//
// Created by avarnier-navarro on 25/03/2022.
//

#pragma once

#include "../ScriptablePipeline/EngineObjects/GameObject.h"

class Cube : public GameObject{

public:

    Cube(App* app);
    void DrawRightFace();
    void DrawLeftFace();
    void DrawTopFace();
    void DrawDownFace();
    void DrawFrontFace();
    void DrawBackFace();
};
