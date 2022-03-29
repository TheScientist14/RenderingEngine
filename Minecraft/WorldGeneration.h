//
// Created by ewakeford on 18/03/2022.
//

#pragma once


#include <vector>
#include <memory>
#include "Cube.h"
#include "Quad.h"

using namespace std;

class GameObject;
class App;
class Cube;

typedef vector<int> VectorCubeObject1D;
typedef vector<shared_ptr<Quad>> VectorQuadObject1D;

class WorldGeneration {

public:

    WorldGeneration(App *prmApp, int prmBockSize, float prmBlockScaleFactor);

    const static int size = 32;
    App *app;
    vec3 chunkCoord;
    int blockSize;
    float blockScaleFactor;
    VectorCubeObject1D cubes;
    VectorQuadObject1D quads;

    void generateWorld(App* prmApp);
    void generateNoise();
    void combineVerticesByAxis();
    VectorCubeObject1D getCubes();
    VectorQuadObject1D getQuads();

    static vec3 worldToChunkCoords(vec3 worldCoord, vec3 chunkCoord, float blockSize);

};


