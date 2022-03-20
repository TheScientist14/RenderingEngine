//
// Created by ewakeford on 18/03/2022.
//

#pragma once


#include "../ScriptablePipeline/EngineObjects/EngineObject.h"

class WorldGeneration {

public:

    WorldGeneration(int prmSize, int prmBockSize, float prmBlockScaleFactor);

    float *generatedNoise;
    int size;
    int blockSize;
    float blockScaleFactor;

    vector<shared_ptr<EngineObject>> generateWorld(App* prmApp) const;
    float* generateNoise() const;


};


