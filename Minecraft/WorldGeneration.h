//
// Created by ewakeford on 18/03/2022.
//

#pragma once


#include <vector>
#include <memory>

using namespace std;

class GameObject;
class App;

typedef vector<shared_ptr<GameObject>> VectorEngineObject1D;

class WorldGeneration {

public:

    WorldGeneration(int prmBockSize, float prmBlockScaleFactor);

    float* generatedNoise;
    const static int size = 16;
    int blockSize;
    float blockScaleFactor;
    VectorEngineObject1D cubes;

    void generateWorld(App* prmApp);
    float* generateNoise();
    VectorEngineObject1D getCubes();

};


